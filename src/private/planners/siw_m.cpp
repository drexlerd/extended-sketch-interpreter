#include "siw_m.hpp"

#include "../extended_sketch/extended_sketch.hpp"
#include "../extended_sketch/extended_state.hpp"
#include "../extended_sketch/rules.hpp"
#include "../extended_sketch/module.hpp"
#include "../dlplan/include/dlplan/policy.h"
#include "../planners/iw_search.hpp"
#include "../planners/atom_registry.hpp"

#include <iostream>
#include <deque>


using namespace std;
using namespace mimir::formalism;
using namespace mimir::extended_sketch;
using namespace dlplan::policy;
using namespace dlplan::core;

namespace mimir::planners {


struct StackEntry {
    Module mod;
    ExtendedState state;
};

SIWMSearch::SIWMSearch(
    const DomainDescription& domain,
    const ProblemDescription& problem,
    const std::shared_ptr<InstanceInfo> instance_info,
    const extended_sketch::ModuleList& modules,
    planners::SuccessorGeneratorType successor_generator_type,
    int max_arity)
    : m_domain(domain),
      m_problem(problem),
      m_instance_info(instance_info),
      m_modules(modules),
      m_max_arity(max_arity),
      average_effective_arity(0),
      maximum_effective_arity(0) {
    const auto grounding_time_start = std::chrono::high_resolution_clock::now();
    m_successor_generator = planners::create_sucessor_generator(problem, successor_generator_type);
    const auto grounding_time_end = std::chrono::high_resolution_clock::now();
    statistics.time_grounding_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();
}

bool SIWMSearch::find_plan(ActionList& plan) {
    std::deque<StackEntry> stack;

    auto current_module = m_modules.front();
    auto current_state = current_module->get_extended_sketch()->create_initial_extended_state(m_problem, m_instance_info);

    std::cout << std::endl << "Start SIW_M" << std::endl;
    const auto time_start = std::chrono::high_resolution_clock::now();
    int step = 0;
    int num_iw_searches = 0;
    while (!literals_hold(m_problem->goal, current_state.mimir)) {
        ++step;
        auto extended_sketch = current_module->get_extended_sketch();

        /* Internal memory */
        // Load rule
        ExtendedState successor_state;
        bool applied = extended_sketch->try_apply_load_rule(current_state, step, successor_state);
        if (applied) {
            current_state = successor_state;
            continue;
        }

        // Call rule
        Module callee;
        ExtendedState callee_state;
        applied = extended_sketch->try_apply_call_rule(current_state, step, successor_state, callee, callee_state);
        if (applied) {
            std::cout << "Push callee on stack." << std::endl;
            stack.push_back(StackEntry{ current_module, successor_state });
            current_state = callee_state;
            current_module = callee;
            continue;
        }


        /* External memory */
        // Action rule
        Action action;
        applied = extended_sketch->try_apply_action_rule(m_problem, current_state, step, successor_state, action);
        if (applied) {
            plan.push_back(action);
            current_state = successor_state;
            ++statistics.generated;
            continue;
        }

        // Search rule
        IWSearchStatistics iw_statistics;
        ActionList partial_plan;
        applied = extended_sketch->try_apply_search_rule(m_problem, m_instance_info, m_successor_generator, m_max_arity, current_state, step, successor_state, partial_plan, iw_statistics);
        if (applied) {
            ++num_iw_searches;
            plan.insert(plan.end(), partial_plan.begin(), partial_plan.end());
            current_state = successor_state;
            statistics += iw_statistics;
            average_effective_arity += iw_statistics.effective_arity;
            maximum_effective_arity = std::max(maximum_effective_arity, iw_statistics.effective_arity);
            continue;
        }


        if (stack.empty()) {
            std::cout << "Stack emptied without finding solution." << std::endl;
            for (const auto& action : plan) {
                std::cout << action << std::endl;
            }
            return false;
        } else {
            std::cout << "Pop from stack." << std::endl;
            auto stack_entry = stack.back();
            stack.pop_back();
            current_module =  stack_entry.mod;
            current_state.memory = stack_entry.state.memory;
            current_state.dlplan = std::make_shared<dlplan::core::State>(
                current_state.dlplan->get_index(),
                current_state.dlplan->get_instance_info(),
                current_state.dlplan->get_atom_indices(),
                stack_entry.state.dlplan->get_state_extension());
            std::cout << "Execution back to parent module and memory state " << current_state.memory->compute_signature() << std::endl << std::endl;
            continue;
        }
        return false;
    }
    const auto time_end = std::chrono::high_resolution_clock::now();
    statistics.time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
    statistics.time_total_ns = statistics.time_grounding_ns + statistics.time_search_ns;
    average_effective_arity /= static_cast<double>(num_iw_searches);
    return true;
}

void SIWMSearch::print_statistics(int num_indent) const {
    auto spaces = vector<char>(num_indent, ' ');
    string indent(spaces.begin(), spaces.end());
    statistics.print(num_indent);
    cout << indent << "Average effective width " << average_effective_arity << endl;
    cout << indent << "Maximum effective width " << maximum_effective_arity << endl;
}

}
