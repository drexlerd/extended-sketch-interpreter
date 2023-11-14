#include "extended_sketch.hpp"

#include "declarations.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "rules.hpp"

#include "../planners/iw_search.hpp"


using namespace std;


namespace mimir::extended_sketch {

ExtendedSketchImpl::ExtendedSketchImpl(
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterMap& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Register, int>& register_mapping)
    : m_memory_states(memory_states),
      m_initial_memory_state(initial_memory_state),
      m_registers(registers),
      m_booleans(booleans),
      m_numericals(numericals),
      m_concepts(concepts),
      m_load_rules(load_rules),
      m_call_rules(call_rules),
      m_action_rules(action_rules),
      m_search_rules(search_rules),
      m_sketches_by_memory_state(sketches_by_memory_state),
      m_search_rule_by_rule_by_memory_state(search_rule_by_rule_by_memory_state),
      m_load_rules_by_memory_state(load_rules_by_memory_state),
      m_register_mapping(register_mapping) {
}

bool ExtendedSketchImpl::try_apply_load_rule(
    const ExtendedState& current_state,
    int& step,
    ExtendedState& successor_state) {
    auto it1 = m_load_rules_by_memory_state.find(current_state.memory);
    if (it1 != m_load_rules_by_memory_state.end()) {
        for (const auto& load_rule : it1->second) {
            bool all_conditions_satisfied = true;
            for (const auto& condition : load_rule->get_feature_conditions()) {
                if (!condition->evaluate(*current_state.dlplan)) {
                    all_conditions_satisfied = false;
                    break;
                }
            }
            if (all_conditions_satisfied) {
                std::cout << ++step << ". Apply load rule " << load_rule->compute_signature() << std::endl;
                load_rule->apply(current_state, m_register_mapping, successor_state);
                return true;
            }
        }
    }
    //cout << "No applicable load rule in memory state " << current_state.memory->compute_signature() << endl;
    return false;
}

bool ExtendedSketchImpl::try_apply_search_rule(
    const mimir::formalism::ProblemDescription& problem,
    const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
    const mimir::planners::SuccessorGenerator& successor_generator,
    int max_arity,
    const ExtendedState& current_state,
    int& step,
    ExtendedState& successor_state,
    mimir::formalism::ActionList& plan,
    mimir::planners::IWSearchStatistics& statistics) {

    auto it2 = m_sketches_by_memory_state.find(current_state.memory);
    if (it2 != m_sketches_by_memory_state.end()) {
        auto iw_search = make_unique<mimir::planners::IWSearch>(
            problem,
            instance_info,
            successor_generator,
            max_arity);

        std::cout << ++step << ". Apply search rule";
        std::shared_ptr<const dlplan::policy::Rule> reason;
        mimir::formalism::ActionList partial_plan;
        bool partial_solution_found = iw_search->find_plan(
            it2->second,
            current_state,
            successor_state,
            partial_plan,
            reason);
        statistics = iw_search->statistics;

        if (!partial_solution_found) {
            return false;
        } else {
            plan.insert(plan.end(), partial_plan.begin(), partial_plan.end());
            std::cout << " Partial plan:" << std::endl;
            for (const auto& action : partial_plan) {
                std::cout << "    " << action << std::endl;
            }
        }

        if (!reason) {
            throw std::runtime_error("There should be a reason to reach a goal");
        }
        successor_state.memory = m_search_rule_by_rule_by_memory_state.at(current_state.memory).at(reason)->get_memory_state_effect();
        std::cout << "  Set current memory state to " << successor_state.memory->compute_signature() << std::endl;

        return true;
    }

    // cout << "No applicable search rule in memory state " << current_state.memory->compute_signature() << endl;
    return false;  // unsolved
}

ExtendedState ExtendedSketchImpl::create_initial_extended_state(
    const mimir::formalism::ProblemDescription& problem,
    const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info) {
    std::vector<int> register_contents(m_register_mapping.size(), 0);
    auto current_state = mimir::formalism::create_state(problem->initial, problem);
    std::shared_ptr<const dlplan::core::State> current_dlplan_state = nullptr;
    {
        mimir::planners::DLPlanAtomRegistry atom_registry(problem, instance_info);
        current_dlplan_state = std::make_shared<dlplan::core::State>(
            instance_info,
            atom_registry.convert_state(current_state),
            register_contents,
            std::vector<dlplan::core::ConceptDenotation>{},  // no arguments since it is not wrapped into a module
            0);
    }
    return ExtendedState{
        m_initial_memory_state,
        current_state,
        current_dlplan_state
    };
}


const CallRuleList& ExtendedSketchImpl::get_call_rules() const {
    return m_call_rules;
}


std::string ExtendedSketchImpl::compute_signature() const {
    std::stringstream ss;
    ss << "(:extended_sketch\n"
       << "(:memory_states ";
    for (const auto& pair : m_memory_states) {
        ss << pair.second->compute_signature() << " ";
    }
    ss << ")\n";  // memory_states
    ss << "(:initial_memory_state " << m_initial_memory_state->compute_signature() << ")\n";
    ss << "(:registers ";
    for (const auto& pair : m_registers) {
        ss << pair.second->compute_signature() << " ";
    }
    ss << ")\n";  // register
    ss << "(:booleans ";
    for (const auto& pair : m_booleans) {
        ss << "(" << pair.first << " \"" << pair.second->get_boolean()->compute_repr() << "\") ";
    }
    ss << ")\n";  // booleans
    ss << "(:numericals ";
    for (const auto& pair : m_numericals) {
        ss << "(" << pair.first << " \"" << pair.second->get_numerical()->compute_repr() << "\") ";
    }
    ss << ")\n";  // numericals
    ss << "(:concepts ";
    for (const auto& pair : m_concepts) {
        ss << "(" << pair.first << " \"" << pair.second->get_concept()->compute_repr() << "\") ";
    }
    ss << ")\n";  // concepts
    for (const auto& load_rule : m_load_rules) {
        ss << load_rule->compute_signature() << "\n";
    }
    for (const auto& call_rule : m_call_rules) {
        ss << call_rule->compute_signature() << "\n";
    }
    for (const auto& action_rule : m_action_rules) {
        ss << action_rule->compute_signature() << "\n";
    }
    for (const auto& search_rule : m_search_rules) {
        ss << search_rule->compute_signature() << "\n";
    }
    ss << ")";  // extended_sketch
    return ss.str();
}

ExtendedSketch make_extended_sketch(
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterMap& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Register, int>& register_mapping) {
    return std::make_shared<ExtendedSketchImpl>(
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules,
        sketches_by_memory_state, search_rule_by_rule_by_memory_state,
        load_rules_by_memory_state, register_mapping);
}

}