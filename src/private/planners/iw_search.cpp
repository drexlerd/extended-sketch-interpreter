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
        const planners::SuccessorGenerator& successor_generator,
        int max_arity) : problem_(problem),
                         instance_info_(instance_info),
                         successor_generator_(successor_generator),
                         max_arity_(max_arity),
                         print_(false),
                         random_generator_(std::make_unique<RandomGenerator>()),
                         g_value_(0)
    {
    }

    IWSearch::~IWSearch() { }

    bool IWSearch::width_zero_search(
        const mimir::extended_sketch::ExtendedState& initial_state,
        ExtendedSketchGoalTest& goal_test,
        mimir::extended_sketch::ExtendedState& final_state,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        std::shared_ptr<const dlplan::policy::Rule>& reason)
    {
        uint32_t initial_state_index = state_registry.find_state(initial_state.mimir);
        assert(initial_state_index != StateRegistry::no_state);
        if (g_values_.size() <= initial_state_index) {
            g_values_.resize(2 * initial_state_index + 1, std::numeric_limits<int>::max());
        }
        g_values_[initial_state_index] = 0;
        std::cout << "[" << 0 << "]" << std::flush;

        StateData state_data = StateData{
            initial_state_index,
            initial_state,
        };


        const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
        auto goal_test_result = goal_test.test_goal(state_data);
        const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
        statistics.time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();
        if (goal_test_result.is_goal)
        {
            final_state = state_data.extended_state;
            reason = goal_test_result.reason;
            return true;
        }

        ++statistics.expanded;
        const auto grounding_time_start = std::chrono::high_resolution_clock::now();
        auto applicable_actions = successor_generator_->get_applicable_actions(initial_state.mimir);
        std::shuffle(applicable_actions.begin(), applicable_actions.end(), random_generator_->random_generator);
        const auto grounding_time_end = std::chrono::high_resolution_clock::now();
        statistics.time_successors_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();

        for (const auto &action : applicable_actions)
        {
            const auto apply_time_start = std::chrono::high_resolution_clock::now();
            const auto successor_state = formalism::apply(action, initial_state.mimir);
            const auto apply_time_end = std::chrono::high_resolution_clock::now();
            statistics.time_apply_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(apply_time_end - apply_time_start).count();

            uint32_t successor_state_index = state_registry.find_state(successor_state);
            if (successor_state_index == StateRegistry::no_state)
            {
                ++statistics.generated;
                successor_state_index = state_registry.register_state(successor_state);
                int g_value = 1;
                if (g_value > g_value_) {
                    g_value_ = g_value;
                    std::cout << "[" << g_value_ << "]" << std::flush;
                }
                StateData successor_state_data = StateData{
                    successor_state_index,
                    mimir::extended_sketch::ExtendedState{
                        initial_state.memory,
                        successor_state,
                        std::make_shared<dlplan::core::State>(instance_info_,
                            atom_registry.convert_state(successor_state),
                            initial_state.dlplan->get_register_contents(),
                            initial_state.dlplan->get_argument_contents(),
                            successor_state_index)
                    }
                };

                const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                auto goal_test_result = goal_test.test_goal(successor_state_data);
                const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                statistics.time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();
                if (goal_test_result.is_goal)
                {
                    plan.push_back(action);
                    final_state = successor_state_data.extended_state;
                    reason = goal_test_result.reason;
                    return true;
                }
            }
        }
        return false;
    }

    bool IWSearch::width_arity_search(
        const mimir::extended_sketch::ExtendedState& initial_state,
        ExtendedSketchGoalTest& goal_test,
        mimir::extended_sketch::ExtendedState& final_state,
        int arity,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
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
            uint32_t initial_state_index = state_registry.find_state(initial_state.mimir);
            if (initial_state_index == StateRegistry::no_state)
            {
                initial_state_index = state_registry.register_state(initial_state.mimir);
            }

            uint32_t context_index = state_to_context_index.get_context_index(initial_state_index);
            if (context_index == StateToContextIndex::not_exists)
            {
                if (g_values_.size() <= initial_state_index) {
                    g_values_.resize(2 * initial_state_index + 1, std::numeric_limits<int>::max());
                }
                g_values_[initial_state_index] = 0;
                std::cout << "[" << 0 << "]" << std::flush;
                StateData state_data = StateData{ initial_state_index, initial_state };

                if (test_prune({}, state_data.extended_state.dlplan->get_atom_indices(), novelty_table))
                {
                    ++statistics.pruned;
                    assert(context_index == StateToContextIndex::not_exists);
                }
                else
                {
                    ++statistics.generated;

                    const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                    const auto goal_test_result = goal_test.test_goal(state_data);
                    const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                    statistics.time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();

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

        while ((queue.size() > 0))
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
                std::cout << "[f = " << context.fringe_value << "] Expanded: " << statistics.expanded << "; Generated: " << statistics.generated << " (" << fringe_time_ms
                          << " ms)" << std::endl;
            }

            context.is_expanded = true;
            search_space.set_context(context_index, context);
            ++statistics.expanded;
            const auto grounding_time_start = std::chrono::high_resolution_clock::now();
            const auto state = state_registry.lookup_state(context.state_index);
            StateData state_data = StateData{
                state_index,
                mimir::extended_sketch::ExtendedState {
                    initial_state.memory,
                    state,
                    std::make_shared<dlplan::core::State>(instance_info_,
                        atom_registry.convert_state(state),
                        initial_state.dlplan->get_register_contents(),
                        initial_state.dlplan->get_argument_contents(),
                        state_index),
                }
            };
            auto applicable_actions = successor_generator_->get_applicable_actions(state);
            std::shuffle(applicable_actions.begin(), applicable_actions.end(), random_generator_->random_generator);
            const auto grounding_time_end = std::chrono::high_resolution_clock::now();
            statistics.time_successors_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();

            for (const auto &action : applicable_actions)
            {
                const auto apply_time_start = std::chrono::high_resolution_clock::now();
                const auto successor_state = formalism::apply(action, state);
                const auto apply_time_end = std::chrono::high_resolution_clock::now();
                statistics.time_apply_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(apply_time_end - apply_time_start).count();

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
                        mimir::extended_sketch::ExtendedState {
                            initial_state.memory,
                            successor_state,
                            std::make_shared<dlplan::core::State>(instance_info_,
                                atom_registry.convert_state(successor_state),
                                initial_state.dlplan->get_register_contents(),
                                initial_state.dlplan->get_argument_contents(),
                                successor_state_index)
                        }
                    };
                    if (test_prune(state_data.extended_state.dlplan->get_atom_indices(), successor_state_data.extended_state.dlplan->get_atom_indices(), novelty_table))
                    {
                        ++statistics.pruned;
                        assert(successor_context_index == StateToContextIndex::not_exists);
                    }
                    else
                    {
                        ++statistics.generated;

                        const auto goal_test_time_start = std::chrono::high_resolution_clock::now();
                        const auto goal_test_result = goal_test.test_goal(successor_state_data);
                        const auto goal_test_time_end = std::chrono::high_resolution_clock::now();
                        statistics.time_goal_test_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(goal_test_time_end - goal_test_time_start).count();

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
                            final_state = successor_state_data.extended_state;
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
        const std::shared_ptr<const dlplan::policy::Policy>& sketch,
        const mimir::extended_sketch::ExtendedState& initial_state,
        mimir::extended_sketch::ExtendedState& final_state,
        std::vector<formalism::Action> &plan,
        std::shared_ptr<const dlplan::policy::Rule>& reason) {
        statistics = IWSearchStatistics();

        const auto time_start = std::chrono::high_resolution_clock::now();

        auto found_solution = false;
        StateRegistry state_registry;

        // Initialize dlplan state with respect to a new atom registry.
        auto atom_registry = DLPlanAtomRegistry(problem_, instance_info_);
        uint32_t initial_state_index = state_registry.find_state(initial_state.mimir);
        if (initial_state_index == StateRegistry::no_state) {
            initial_state_index = state_registry.register_state(initial_state.mimir);
        }
        auto initial_state_prime =
            mimir::extended_sketch::ExtendedState {
                initial_state.memory,
                initial_state.mimir,
                std::make_shared<dlplan::core::State>(instance_info_,
                    atom_registry.convert_state(initial_state.mimir),
                    initial_state.dlplan->get_register_contents(),
                    initial_state.dlplan->get_argument_contents(),
                    initial_state_index)
        };
        ExtendedSketchGoalTest goal_test = ExtendedSketchGoalTest(problem_, instance_info_, sketch, initial_state_prime);

        for (int arity = 0; arity <= max_arity_; ++arity)
        {
            if (arity == 0)
            {
                if (width_zero_search(initial_state_prime, goal_test, final_state, state_registry, atom_registry, plan, reason))
                {
                    statistics.effective_arity = arity;
                    found_solution = true;
                    break;
                }
            }
            else
            {
                std::cout << "  ";
                if (width_arity_search(initial_state_prime, goal_test, final_state, arity, state_registry, atom_registry, plan, reason))
                {
                    statistics.effective_arity = arity;
                    found_solution = true;
                    break;
                }
            }
        }

        const auto time_end = std::chrono::high_resolution_clock::now();
        statistics.time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
        statistics.time_total_ns = statistics.time_grounding_ns + statistics.time_search_ns;
        return found_solution;
    }
}
