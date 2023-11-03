#include "siw_r.hpp"

#include <iostream>
#include <iomanip>

#include "src/private/extended_sketch/extended_sketch.hpp"
#include "src/private/extended_sketch/rules.hpp"
#include "src/private/dlplan/include/dlplan/policy.h"
#include "src/private/planners/iw_search.hpp"
#include "src/private/planners/atom_registry.hpp"


using namespace std;
using namespace mimir::formalism;
using namespace mimir::extended_sketch;
using namespace dlplan::policy;
using namespace dlplan::core;

namespace mimir::extended_sketch {

SIWRSearch::SIWRSearch(
    const DomainDescription& domain,
    const ProblemDescription& problem,
    const std::shared_ptr<InstanceInfo> instance_info,
    const std::shared_ptr<PolicyFactory> policy_factory,
    const ExtendedSketch& extended_sketch)
    : m_domain(domain),
      m_problem(problem),
      m_instance_info(instance_info),
      m_policy_factory(policy_factory),
      m_extended_sketch(extended_sketch) { }

bool SIWRSearch::find_plan(vector<Action>& plan) {
    pruned = 0;
    generated = 0;
    expanded = 0;
    time_successors_ns = 0;
    time_apply_ns = 0;
    time_goal_test_ns = 0;
    time_search_ns = 0;
    time_total_ns = 0;
    average_effective_arity = 0;
    maximum_effective_arity = 0;

    // Initialization
    auto current_state = create_state(m_problem->initial, m_problem);
    std::shared_ptr<const dlplan::core::State> current_dlplan_state = nullptr;
    {
        mimir::planners::DLPlanAtomRegistry atom_registry(m_problem, m_instance_info);
        current_dlplan_state = std::make_shared<dlplan::core::State>(m_instance_info, atom_registry.convert_state(current_state), 0);
    }
    MemoryState current_memory_state = m_extended_sketch->get_initial_memory_state();
    unordered_map<Register, int> register_mapping;
    vector<int> register_contents;
    for (const auto& pair : m_extended_sketch->get_registers()) {
        register_mapping.emplace(pair.second, register_contents.size());
        register_contents.push_back(0);  // random initialization
    }
    // Build sketches for external rules, one for each memory state
    std::cout << "Group search rules by memory state" << std::endl;
    unordered_map<MemoryState, vector<SearchRule>> search_rules_by_memory_state;
    for (const auto& search_rule : m_extended_sketch->get_search_rules()) {
        search_rules_by_memory_state[search_rule->get_memory_state_condition()].push_back(search_rule);
    }
    unordered_map<MemoryState, shared_ptr<const Policy>> sketches_by_memory_state;
    unordered_map<shared_ptr<const Rule>, MemoryState> rule_to_memory_effect;
    for (const auto& pair : search_rules_by_memory_state) {
        Rules sketch_rules;
        for (const auto& search_rule : pair.second) {
            auto sketch_rule = m_policy_factory->make_rule(search_rule->get_feature_conditions(), search_rule->get_feature_effects());
            rule_to_memory_effect.emplace(sketch_rule, search_rule->get_memory_state_effect());
            sketch_rules.insert(sketch_rule);
        }
        auto sketch = m_policy_factory->make_policy(sketch_rules);
        sketches_by_memory_state[pair.first] = sketch;
    }
    // Group loadrules by internal memory
    std::cout << "Group load rules by memory state" << std::endl;
    unordered_map<MemoryState, vector<LoadRule>> load_rules_by_memory_state;
    for (const auto& load_rule : m_extended_sketch->get_load_rules()) {
        load_rules_by_memory_state[load_rule->get_memory_state_condition()].push_back(load_rule);
    }
    // Initialize IWRSearch
    int max_arity = 2;
    m_iw_search = make_unique<mimir::planners::IWSearch>(
        m_problem,
        m_instance_info,
        mimir::planners::SuccessorGeneratorType::LIFTED,
        sketches_by_memory_state,
        max_arity);


    std::cout << std::endl << "Start search" << std::endl;
    dlplan::core::DenotationsCaches denotation_caches;
    const auto time_start = std::chrono::high_resolution_clock::now();
    int step = 0;
    while (!literals_hold(m_problem->goal, current_state)) {
        // Find rules for current memory state
        auto it1 = load_rules_by_memory_state.find(current_memory_state);
        if (it1 != load_rules_by_memory_state.end()) {
            bool applied_load = false;
            for (const auto& load_rule : it1->second) {
                bool all_conditions_satisfied = true;
                for (const auto& condition : load_rule->get_feature_conditions()) {
                    if (!condition->evaluate(*current_dlplan_state, denotation_caches)) {
                        all_conditions_satisfied = false;
                        break;
                    }
                }
                if (all_conditions_satisfied) {
                    std::cout << ++step << ". Apply load rule " << load_rule->compute_signature() << std::endl;
                    load_rule->apply(*current_dlplan_state, register_mapping, denotation_caches, register_contents, current_memory_state);
                    applied_load = true;
                    break;
                }
            }
            if (applied_load) continue;
        }

        auto it2 = sketches_by_memory_state.find(current_memory_state);
        if (it2 != sketches_by_memory_state.end()) {
            std::cout << ++step << ". Apply search rule" << std::endl;
            std::vector<Action> partial_plan;
            mimir::formalism::State final_state;
            std::shared_ptr<const dlplan::core::State> final_dlplan_state;
            std::shared_ptr<const dlplan::policy::Rule> reason;
            bool partial_solution_found = m_iw_search->find_plan(current_state, register_contents, current_memory_state, partial_plan, final_state, final_dlplan_state, reason);
            pruned += m_iw_search->pruned;
            generated += m_iw_search->generated;
            expanded += m_iw_search->expanded;
            time_successors_ns += m_iw_search->time_successors_ns;
            time_apply_ns += m_iw_search->time_apply_ns;
            time_goal_test_ns += m_iw_search->time_goal_test_ns;

            if (partial_solution_found) {
                average_effective_arity += m_iw_search->effective_arity;
                maximum_effective_arity = std::max(maximum_effective_arity, m_iw_search->effective_arity);
                std::cout << "  Compatible rule: " << reason->str() << std::endl;
                std::cout << "  Partial plan: " << std::endl;
                for (const auto& action : partial_plan)
                {
                    std::cout << "    " << action << std::endl;
                }
            } else {
                average_effective_arity = std::numeric_limits<float>::max();
                maximum_effective_arity = std::numeric_limits<int>::max();
                cout << "Failed to find partial solution" << endl;
                return false;
            }
            current_state = final_state;
            current_dlplan_state = final_dlplan_state;
            if (!reason) {
                throw std::runtime_error("There should be a reason to reach a goal");
            }
            current_memory_state = rule_to_memory_effect.at(reason);
            std::cout << "  Set current memory state to " << current_memory_state->compute_signature() << std::endl;
            continue;
        }

        cout << "No applicable rule in extended sketch" << endl;
        return false;  // unsolved
    }
    const auto time_end = std::chrono::high_resolution_clock::now();
    time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
    time_total_ns = m_iw_search->time_grounding_ns + time_search_ns;
    return true;  // solved
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
    m_iw_search->get_goal_test().print_statistics(num_indent);
    cout << indent << "Search time: " << time_search_ns / (int64_t) 1E6 << " ms" << endl;
    cout << indent << "Total time: " << time_total_ns / (int64_t) 1E6 << " ms" << endl;
}

}
