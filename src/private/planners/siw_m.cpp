#include "siw_m.hpp"

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
    
}

void SIWMSearch::print_statistics(int num_indent) const {
    auto spaces = vector<char>(num_indent, ' ');
    string indent(spaces.begin(), spaces.end());
    statistics.print(num_indent);
    cout << indent << "Average effective width " << average_effective_arity << endl;
    cout << indent << "Maximum effective width " << maximum_effective_arity << endl;
}

}
