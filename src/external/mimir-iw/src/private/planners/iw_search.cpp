#include "iw_search.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <limits>
#include <deque>
#include <limits>
#include <unordered_map>
#include <iomanip>


namespace mimir::planners
{

    static bool test_prune(
        const std::vector<int>& source_atom_indices,
        const std::vector<int>& target_atom_indices,
        dlplan::novelty::NoveltyTable& novelty_table)
    {
        assert(std::is_sorted(source_atom_indices.begin(), source_atom_indices.end()) &&
               std::is_sorted(target_atom_indices.begin(), target_atom_indices.end()));
        int max_index = 0;
        int i = 0;
        int j = 0;
        std::vector<int> atom_indices;
        std::vector<int> add_atom_indices;
        atom_indices.reserve(target_atom_indices.size());
        add_atom_indices.reserve(target_atom_indices.size());
        while (i < static_cast<int>(source_atom_indices.size()) && j < static_cast<int>(target_atom_indices.size()))
        {
            if (source_atom_indices[i] < target_atom_indices[j])
            {
                ++i;
            }
            else if (source_atom_indices[i] > target_atom_indices[j])
            {
                add_atom_indices.push_back(target_atom_indices[j]);
                max_index = std::max(max_index, target_atom_indices[j]);
                ++j;
            }
            else
            {
                atom_indices.push_back(target_atom_indices[j]);
                max_index = std::max(max_index, target_atom_indices[j]);
                ++i;
                ++j;
            }
        }
        // add remaining indices.
        for (; j < static_cast<int>(target_atom_indices.size()); ++j)
        {
            add_atom_indices.push_back(target_atom_indices[j]);
            max_index = std::max(max_index, target_atom_indices[j]);
        }

        // increase table capacity.
        int capacity = novelty_table.get_novelty_base()->get_num_atoms() - 1;
        if (max_index > capacity)
        {
            novelty_table.resize(
                std::make_shared<dlplan::novelty::NoveltyBase>(
                    2 * max_index + 1,
                    novelty_table.get_novelty_base()->get_arity()));
        }
        bool novel = novelty_table.insert_atom_indices(atom_indices, add_atom_indices, false);
        return !novel;
    }

    IWSearch::IWSearch(
        const formalism::ProblemDescription &problem,
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
        planners::SuccessorGeneratorType successor_generator_type,
        const std::unordered_map<sketches::extended_sketch::MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
        int max_arity) : problem_(problem),
                         instance_info_(instance_info),
                         successor_generator_(nullptr),
                         goal_test_(ExtendedSketchGoalTest(problem, instance_info, sketches_by_memory_state)),
                         max_arity_(max_arity),
                         print_(false),
                         random_generator_(std::make_unique<RandomGenerator>()),
                         g_value_(0),
                         pruned(0),
                         generated(0),
                         expanded(0),
                         max_expanded(std::numeric_limits<uint32_t>::max()),
                         effective_arity(0),
                         time_successors_ns(0),
                         time_apply_ns(0),
                         time_goal_test_ns(0),
                         time_grounding_ns(0),
                         time_search_ns(0),
                         time_total_ns(0)
    {
        const auto grounding_time_start = std::chrono::high_resolution_clock::now();
        successor_generator_ = planners::create_sucessor_generator(problem_, successor_generator_type);
        const auto grounding_time_end = std::chrono::high_resolution_clock::now();
        time_grounding_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();
    }

    IWSearch::~IWSearch() { }

    bool IWSearch::width_zero_search(
        const formalism::State& initial_state,
        const std::vector<int>& register_contents,
        const sketches::extended_sketch::MemoryState& memory_state,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        formalism::State &final_state,
        std::shared_ptr<const dlplan::core::State>& final_dlplan_state,
        std::shared_ptr<const dlplan::policy::Rule>& reason)
    {
        uint32_t initial_state_index = state_registry.find_state(initial_state);
        if (initial_state_index == StateRegistry::no_state) {
            initial_state_index = state_registry.register_state(initial_state);
        }
        StateData state_data = StateData{
            initial_state_index,
            initial_state,
            std::make_shared<dlplan::core::State>(instance_info_,
                atom_registry.convert_state(initial_state),
                register_contents,
                initial_state_index),
            memory_state
        };

        const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
        goal_test_.set_initial_state(state_data);
        auto goal_test_result = goal_test_.test_goal(state_data);
        const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
        time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();
        if (goal_test_result.is_goal)
        {
            plan.clear();
            final_state = goal_test_result.state;
            final_dlplan_state = goal_test_result.dlplan_state;
            reason = goal_test_result.reason;
            return true;
        }

        ++expanded;
        const auto grounding_time_start = std::chrono::high_resolution_clock::now();
        auto applicable_actions = successor_generator_->get_applicable_actions(initial_state);
        std::shuffle(applicable_actions.begin(), applicable_actions.end(), random_generator_->random_generator);
        const auto grounding_time_end = std::chrono::high_resolution_clock::now();
        time_successors_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();

        for (const auto &action : applicable_actions)
        {
            const auto apply_time_start = std::chrono::high_resolution_clock::now();
            const auto successor_state = formalism::apply(action, initial_state);
            const auto apply_time_end = std::chrono::high_resolution_clock::now();
            time_apply_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(apply_time_end - apply_time_start).count();

            uint32_t successor_state_index = state_registry.find_state(successor_state);
            if (successor_state_index == StateRegistry::no_state)
            {
                ++generated;
                successor_state_index = state_registry.register_state(successor_state);
                StateData successor_state_data = StateData{
                    successor_state_index,
                    successor_state,
                    std::make_shared<dlplan::core::State>(instance_info_,
                        atom_registry.convert_state(successor_state),
                        register_contents,
                        successor_state_index),
                    memory_state
                };

                const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                auto goal_test_result = goal_test_.test_goal(successor_state_data);
                const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();
                if (goal_test_result.is_goal)
                {
                    plan.clear();
                    plan.push_back(action);
                    final_state = goal_test_result.state;
                    final_dlplan_state = goal_test_result.dlplan_state;
                    reason = goal_test_result.reason;
                    return true;
                }
            }
        }
        return false;
    }

    bool IWSearch::width_arity_search(
        const formalism::State& initial_state,
        const std::vector<int>& register_contents,
        const sketches::extended_sketch::MemoryState& memory_state,
        int arity,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        formalism::State &final_state,
        std::shared_ptr<const dlplan::core::State>& final_dlplan_state,
        std::shared_ptr<const dlplan::policy::Rule>& reason)
    {
        const auto time_start = std::chrono::high_resolution_clock::now();

        SearchSpace search_space;
        StateToContextIndex state_to_context_index;
        std::deque<uint32_t> queue;
        g_value_ = 0;
        g_values_.clear();
        dlplan::novelty::NoveltyTable novelty_table(
            std::make_shared<dlplan::novelty::NoveltyBase>(atom_registry.get_num_reached_ranks(), arity));

        {
            uint32_t initial_state_index = state_registry.find_state(initial_state);
            if (initial_state_index == StateRegistry::no_state)
            {
                initial_state_index = state_registry.register_state(initial_state);
            }

            uint32_t context_index = state_to_context_index.get_context_index(initial_state_index);
            if (context_index == StateToContextIndex::not_exists)
            {
                if (g_values_.size() <= initial_state_index) {
                    g_values_.resize(2 * initial_state_index + 1, std::numeric_limits<int>::max());
                }
                g_values_[initial_state_index] = 0;
                std::cout << "[" << 0 << "]" << std::flush;
                StateData state_data = StateData{
                    initial_state_index,
                    initial_state,
                    std::make_shared<dlplan::core::State>(instance_info_,
                        atom_registry.convert_state(initial_state),
                        register_contents,
                        initial_state_index),
                    memory_state
                };

                if (test_prune({}, state_data.dlplan_state->get_atom_indices(), novelty_table))
                {
                    ++pruned;
                    assert(context_index == StateToContextIndex::not_exists);
                }
                else
                {
                    ++generated;

                    const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                    const auto goal_test_result = goal_test_.test_goal(state_data);
                    const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                    time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();

                    uint32_t successor_context_index = search_space.add_context(
                        SearchContext(
                            nullptr,
                            initial_state_index,
                            std::numeric_limits<uint32_t>::max(),
                            0,
                            goal_test_result.is_goal,
                            false));
                    state_to_context_index.set_context_index(initial_state_index, successor_context_index);
                    queue.push_back(initial_state_index);
                }
            }
        }

        uint32_t last_fringe_value = 0;

        while ((queue.size() > 0) && (expanded < max_expanded))
        {
            auto state_index = queue.front();
            queue.pop_front();

            auto context_index = state_to_context_index.get_context_index(state_index);
            auto context = search_space.get_context(context_index);
            assert(!context.is_expanded);

            if (print_ && (context.fringe_value > last_fringe_value))
            {
                last_fringe_value = context.fringe_value;
                const auto fringe_time_end = std::chrono::high_resolution_clock::now();
                const auto fringe_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(fringe_time_end - time_start).count();
                std::cout << "[f = " << context.fringe_value << "] Expanded: " << expanded << "; Generated: " << generated << " (" << fringe_time_ms
                          << " ms)" << std::endl;
            }

            context.is_expanded = true;
            search_space.set_context(context_index, context);
            ++expanded;
            const auto grounding_time_start = std::chrono::high_resolution_clock::now();
            const auto state = state_registry.lookup_state(context.state_index);
            StateData state_data = StateData{
                state_index,
                state,
                std::make_shared<dlplan::core::State>(instance_info_,
                    atom_registry.convert_state(state),
                    register_contents,
                    state_index),
                memory_state
            };
            auto applicable_actions = successor_generator_->get_applicable_actions(state);
            std::shuffle(applicable_actions.begin(), applicable_actions.end(), random_generator_->random_generator);
            const auto grounding_time_end = std::chrono::high_resolution_clock::now();
            time_successors_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();

            for (const auto &action : applicable_actions)
            {
                const auto apply_time_start = std::chrono::high_resolution_clock::now();
                const auto successor_state = formalism::apply(action, state);
                const auto apply_time_end = std::chrono::high_resolution_clock::now();
                time_apply_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(apply_time_end - apply_time_start).count();

                uint32_t successor_state_index = state_registry.find_state(successor_state);
                if (successor_state_index == StateRegistry::no_state)
                {
                    successor_state_index = state_registry.register_state(successor_state);
                }

                uint32_t successor_context_index = state_to_context_index.get_context_index(successor_state_index);
                if (successor_context_index == StateToContextIndex::not_exists)
                {
                    if (g_values_.size() <= successor_state_index) {
                        g_values_.resize(2 * successor_state_index + 1, std::numeric_limits<int>::max());
                    }
                    int g_value = g_values_[successor_state_index] = g_values_[context.state_index] + 1;
                    if (g_value > g_value_) {
                        g_value_ = g_value;
                        std::cout << "[" << g_value_ << "]" << std::flush;
                    }
                    StateData successor_state_data = StateData{
                        successor_state_index,
                        successor_state,
                        std::make_shared<dlplan::core::State>(instance_info_,
                            atom_registry.convert_state(successor_state),
                            register_contents,
                            successor_state_index),
                        memory_state
                    };
                    if (test_prune(state_data.dlplan_state->get_atom_indices(), successor_state_data.dlplan_state->get_atom_indices(), novelty_table))
                    {
                        ++pruned;
                        assert(successor_context_index == StateToContextIndex::not_exists);
                    }
                    else
                    {
                        ++generated;

                        const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                        const auto goal_test_result = goal_test_.test_goal(successor_state_data);
                        const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                        time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();

                        uint32_t successor_context_index = search_space.add_context(
                            SearchContext(
                                action,
                                successor_state_index,
                                context_index,
                                context.fringe_value + 1,
                                goal_test_result.is_goal,
                                false));
                        state_to_context_index.set_context_index(successor_state_index, successor_context_index);
                        queue.push_back(successor_state_index);
                        if (goal_test_result.is_goal)
                        {
                            search_space.set_plan(successor_context_index, plan);
                            final_state = goal_test_result.state;
                            final_dlplan_state = goal_test_result.dlplan_state;
                            reason = goal_test_result.reason;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool IWSearch::find_plan(
        const formalism::State& initial_state,
        const std::vector<int>& register_contents,
        const sketches::extended_sketch::MemoryState& memory_state,
        std::vector<formalism::Action> &plan,
        formalism::State& final_state,
        std::shared_ptr<const dlplan::core::State>& final_dlplan_state,
        std::shared_ptr<const dlplan::policy::Rule>& reason) {
        pruned = 0;
        generated = 0;
        expanded = 0;
        time_goal_test_ns = 0;
        time_successors_ns = 0;
        time_apply_ns = 0;
        time_search_ns = 0;

        const auto time_start = std::chrono::high_resolution_clock::now();

        auto found_solution = false;
        StateRegistry state_registry;
        auto atom_registry = DLPlanAtomRegistry(problem_, instance_info_);
        for (int arity = 0; arity <= max_arity_; ++arity)
        {
            effective_arity = arity;
            if (arity == 0)
            {
                if (width_zero_search(initial_state, register_contents, memory_state, state_registry, atom_registry, plan, final_state, final_dlplan_state, reason))
                {
                    found_solution = true;
                    break;
                }
            }
            else
            {
                std::cout << std::endl;
                if (width_arity_search(initial_state, register_contents, memory_state, arity, state_registry, atom_registry, plan, final_state, final_dlplan_state, reason))
                {
                    found_solution = true;
                    break;
                }
            }
        }
        if (!found_solution) {
            effective_arity = std::numeric_limits<uint32_t>::max();
        }

        const auto time_end = std::chrono::high_resolution_clock::now();
        time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
        time_total_ns = time_grounding_ns + time_search_ns;
        return found_solution;
    }

    void IWSearch::print_statistics(int num_indent) const {
        auto spaces = std::vector<char>(num_indent, ' ');
        std::string indent(spaces.begin(), spaces.end());
        std::cout << indent << "Expanded " << expanded << " states" << std::endl;
        std::cout << indent << "Generated " << generated << " states" << std::endl;
        std::cout << indent << "Pruned " << pruned << " states" << std::endl;
        std::cout << indent << "Effective width " << effective_arity << std::endl;
        std::cout << indent << "Successor time: " << time_successors_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_successors_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Apply time: " << time_apply_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_apply_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Grounding time: " << time_grounding_ns / (int64_t) 1E6 << " ms"
                    << " (" << std::fixed << std::setprecision(3) << (100.0 * time_grounding_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Goal time: " << time_goal_test_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_goal_test_ns) / time_total_ns << "%)" << std::endl;
        goal_test_.print_statistics(num_indent);
        std::cout << indent << "Search time: " << time_search_ns / (int64_t) 1E6 << " ms" << std::endl;
        std::cout << indent << "Total time: " << time_total_ns / (int64_t) 1E6 << " ms" << std::endl;
    }

    const ExtendedSketchGoalTest& IWSearch::get_goal_test() const {
        return goal_test_;
    }
}
