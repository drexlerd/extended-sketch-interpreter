#include "siw_r.hpp"

#include "src/extended_sketch/extended_sketch.hpp"
#include "src/extended_sketch/rules.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"

using namespace std;
using namespace mimir::formalism;
using namespace sketches::extended_sketch;
using namespace dlplan::policy;
using namespace dlplan::core;

namespace sketches {

SIWRSearch::SIWRSearch(
    const DomainDescription& domain,
    const ProblemDescription& problem,
    const std::shared_ptr<PolicyFactory> policy_factory,
    const ExtendedSketch& extended_sketch)
    : m_domain(domain), m_problem(problem), m_policy_factory(policy_factory), m_extended_sketch(extended_sketch) { }

bool SIWRSearch::find_plan(vector<Action>& plan) {
    // Initialization
    MemoryState current_memory_state = m_extended_sketch->get_initial_memory_state();
    unordered_map<Register, int> register_mapping;
    vector<int> register_contents;
    for (const auto& pair : m_extended_sketch->get_registers()) {
        register_mapping.emplace(pair.second, register_contents.size());
        register_contents.push_back(0);  // random initialization
    }
    // Build sketches for external rules, one for each memory state
    unordered_map<MemoryState, vector<SearchRule>> search_rules_by_memory_state;
    for (const auto& search_rule : m_extended_sketch->get_search_rules()) {
        search_rules_by_memory_state[search_rule->get_memory_state_condition()].push_back(search_rule);
    }
    unordered_map<MemoryState, shared_ptr<const Policy>> sketches_by_memory_state;
    for (const auto& pair : search_rules_by_memory_state) {
        Rules sketch_rules;
        for (const auto& search_rule : pair.second) {
            auto sketch_rule = m_policy_factory->make_rule(search_rule->get_feature_conditions(), search_rule->get_feature_effects());
            sketch_rules.insert(sketch_rule);
        }
        auto sketch = m_policy_factory->make_policy(sketch_rules);
        sketches_by_memory_state[pair.first] = sketch;
    }
    // group loadrules by internal memory
    unordered_map<MemoryState, vector<LoadRule>> load_rules_by_memory_state;
    for (const auto& load_rule : m_extended_sketch->get_load_rules()) {
        load_rules_by_memory_state[load_rule->get_memory_state_condition()].push_back(load_rule);
    }
    // TODO: find rules for current memory state


    // 1. If internal memory:
    // TODO: implement semantics of load rule
    // 2. Else IWRSearch
    // TODO: we must build sketches for all rules from the same memorystate.
    //       Then simply apply the respective sketch to find subgoal state.
}

void SIWRSearch::print_statistics(int num_indent) const {
    auto spaces = vector<char>(num_indent, ' ');
    string indent(spaces.begin(), spaces.end());
    cout << indent << "Expanded " << expanded << " states" << endl;
    cout << indent << "Generated " << generated << " states" << endl;
    cout << indent << "Pruned " << pruned << " states" << endl;
    cout << indent << "Average effective width " << average_effective_arity << endl;
    cout << indent << "Maximum effective width " << maximum_effective_arity << endl;
    cout << indent << "Successor time: " << time_successors_ns / (int64_t) 1E6 << " ms"
            << " (" << fixed << setprecision(3) << (100.0 * time_successors_ns) / time_total_ns << "%)" << endl;
    cout << indent << "Apply time: " << time_apply_ns / (int64_t) 1E6 << " ms"
        << " (" << fixed << setprecision(3) << (100.0 * time_apply_ns) / time_total_ns << "%)" << endl;
    cout << indent << "Grounding time: " << time_grounding_ns / (int64_t) 1E6 << " ms"
            << " (" << fixed << setprecision(3) << (100.0 * time_grounding_ns) / time_total_ns << "%)" << endl;
    cout << indent << "Goal time: " << time_goal_test_ns / (int64_t) 1E6 << " ms"
            << " (" << fixed << setprecision(3) << (100.0 * time_goal_test_ns) / time_total_ns << "%)" << endl;
    inner_search_.get_goal_test()->print_statistics();
    cout << indent << "Search time: " << time_search_ns / (int64_t) 1E6 << " ms" << endl;
    cout << indent << "Total time: " << time_total_ns / (int64_t) 1E6 << " ms" << endl;
}

}
