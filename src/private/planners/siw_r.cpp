#include "siw_r.hpp"

#include <iostream>

#include "../extended_sketch/extended_sketch.hpp"
#include "../extended_sketch/extended_state.hpp"
#include "../extended_sketch/rules.hpp"
#include "../dlplan/include/dlplan/policy.h"
#include "../planners/iw_search.hpp"
#include "../planners/atom_registry.hpp"


using namespace std;
using namespace mimir::formalism;
using namespace mimir::extended_sketch;
using namespace dlplan::policy;
using namespace dlplan::core;

namespace mimir::planners {

SIWRSearch::SIWRSearch(
    const DomainDescription& domain,
    const ProblemDescription& problem,
    const std::shared_ptr<InstanceInfo> instance_info,
    const ExtendedSketch& extended_sketch,
    planners::SuccessorGeneratorType successor_generator_type,
    int max_arity)
    : m_domain(domain),
      m_problem(problem),
      m_instance_info(instance_info),
      m_extended_sketch(extended_sketch),
      m_max_arity(max_arity),
      average_effective_arity(0),
      maximum_effective_arity(0) {
    const auto grounding_time_start = std::chrono::high_resolution_clock::now();
    m_successor_generator = planners::create_sucessor_generator(problem, successor_generator_type);
    const auto grounding_time_end = std::chrono::high_resolution_clock::now();
    statistics.time_grounding_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(grounding_time_end - grounding_time_start).count();
}

bool SIWRSearch::find_plan(ActionList& plan) {
    // Initialize extended state
    ExtendedState current_state = m_extended_sketch->create_initial_extended_state(m_problem, m_instance_info);

    std::cout << std::endl << "Start SIW_R*" << std::endl;
    const auto time_start = std::chrono::high_resolution_clock::now();
    int step = 0;
    int num_iw_searches = 0;
    while (!literals_hold(m_problem->goal, current_state.mimir)) {
        ++step;
        //if (step == 10) return false;

        {
            const auto [applied, successor_state] = m_extended_sketch->try_apply_load_rule(current_state, step);
            if (applied) {
                current_state = successor_state;
                continue;
            }
        }

        {
            const auto [applied, successor_state, iw_statistics] = m_extended_sketch->try_apply_search_rule(m_problem, m_instance_info, m_successor_generator, m_max_arity, current_state, step, plan);
            if (applied) {
                ++num_iw_searches;
                current_state = successor_state;
                statistics += iw_statistics;
                average_effective_arity += iw_statistics.effective_arity;
                maximum_effective_arity = std::max(maximum_effective_arity, iw_statistics.effective_arity);
                continue;
            }
        }
        return false;
    }
    const auto time_end = std::chrono::high_resolution_clock::now();
    statistics.time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
    statistics.time_total_ns = statistics.time_grounding_ns + statistics.time_search_ns;
    average_effective_arity /= static_cast<double>(num_iw_searches);
    return true;  // solved
}

void SIWRSearch::print_statistics(int num_indent) const {
    auto spaces = vector<char>(num_indent, ' ');
    string indent(spaces.begin(), spaces.end());
    statistics.print(num_indent);
    cout << indent << "Average effective width " << average_effective_arity << endl;
    cout << indent << "Maximum effective width " << maximum_effective_arity << endl;
}

}
