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
    ExtendedState initial_state;
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
    auto entry_module = m_modules.front();
    auto current_state = entry_module->get_extended_sketch()->create_initial_extended_state(m_problem, m_instance_info);
    stack.push_back(StackEntry{ entry_module, current_state });

    int step = 0;
    int num_iw_searches = 0;
    while (!literals_hold(m_problem->goal, current_state.mimir)) {
        if (stack.empty()) {
            std::cout << "Stack emptied without finding solution." << std::endl;
            return false;
        }
        ++step;

        auto entry = stack.back();
        auto extended_sketch = entry.mod->get_extended_sketch();

        ExtendedState successor_state;

        bool applied = extended_sketch->try_apply_load_rule(current_state, step, successor_state);
        if (applied) {
            current_state = successor_state;
            continue;
        }

        IWSearchStatistics iw_statistics;
        applied = extended_sketch->try_apply_search_rule(m_problem, m_instance_info, m_successor_generator, m_max_arity, current_state, step, successor_state, plan, iw_statistics);
        if (applied) {
            ++num_iw_searches;
            current_state = successor_state;
            statistics += iw_statistics;
            average_effective_arity += iw_statistics.effective_arity;
            maximum_effective_arity = std::max(maximum_effective_arity, iw_statistics.effective_arity);
            continue;
        }

        /* Internal memory */
        // Load rule
        // Call rule

        /* External memory */
        // Search rule
        // Action rule

        // If no rule used then pop rule
        stack.pop_back();
    }
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