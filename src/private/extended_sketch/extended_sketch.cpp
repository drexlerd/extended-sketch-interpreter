#include "extended_sketch.hpp"

#include "module.hpp"
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
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const RoleMap& roles,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Concept, int>& register_mapping)
    : m_memory_states(memory_states),
      m_initial_memory_state(initial_memory_state),
      m_booleans(booleans),
      m_numericals(numericals),
      m_concepts(concepts),
      m_roles(roles),
      m_load_rules(load_rules),
      m_call_rules(call_rules),
      m_action_rules(action_rules),
      m_search_rules(search_rules),
      m_sketches_by_memory_state(sketches_by_memory_state),
      m_search_rule_by_rule_by_memory_state(search_rule_by_rule_by_memory_state),
      m_load_rules_by_memory_state(load_rules_by_memory_state),
      m_register_mapping(register_mapping) {
}

std::tuple<bool, ExtendedState> ExtendedSketchImpl::try_apply_load_rule(
    const ExtendedState& current_state,
    int step) const {
    auto it1 = m_load_rules_by_memory_state.find(current_state.memory);
    if (it1 != m_load_rules_by_memory_state.end()) {
        for (const auto& load_rule : it1->second) {
            if (load_rule->evaluate_conditions(current_state)) {
                std::cout << step << ". Apply load rule " << load_rule->compute_signature() << std::endl;
                auto successor_state = load_rule->apply(current_state, m_register_mapping);
                return std::make_tuple(true, successor_state);
            }
        }
    }
    // cout << "No applicable load rule in memory state " << current_state.memory->compute_signature() << endl;
    return std::make_tuple(false, ExtendedState());
}

std::tuple<bool, ExtendedState, Module, ExtendedState> ExtendedSketchImpl::try_apply_call_rule(
    const ExtendedState& current_state,
    int step) const {
    for (const auto& call_rule : m_call_rules) {
        if (call_rule->evaluate_conditions(current_state)) {
            std::cout << step << ". Apply call rule " << call_rule->compute_signature() << std::endl;
            auto [successor_state, callee, callee_state] = call_rule->apply(current_state);
            return std::make_tuple(true, successor_state, callee, callee_state);
        }
    }
    // cout << "No applicable call rule in memory state " << current_state.memory->compute_signature() << endl;
    return std::make_tuple(false, ExtendedState(), Module(), ExtendedState());
}

std::tuple<bool, ExtendedState, mimir::formalism::Action> ExtendedSketchImpl::try_apply_action_rule(
    const mimir::formalism::ProblemDescription& problem,
    const ExtendedState& current_state,
    int step) {
    for (const auto& action_rule : m_action_rules) {
        if (action_rule->evaluate_conditions(current_state)) {
            std::cout << step << ". Apply action rule " << action_rule->compute_signature() << std::endl;
            auto [successor_state, action] = action_rule->apply(problem, current_state);
            return std::make_tuple(true, successor_state, action);
        }
    }
    // cout << "No applicable action rule in memory state " << current_state.memory->compute_signature() << endl;
    return std::make_tuple(false, ExtendedState(), mimir::formalism::Action());
}

std::tuple<bool, ExtendedState, mimir::planners::IWSearchStatistics> ExtendedSketchImpl::try_apply_search_rule(
    const mimir::formalism::ProblemDescription& problem,
    const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
    const mimir::planners::SuccessorGenerator& successor_generator,
    int max_arity,
    const ExtendedState& current_state,
    int step,
    mimir::formalism::ActionList& plan) const {

    auto it2 = m_sketches_by_memory_state.find(current_state.memory);
    if (it2 != m_sketches_by_memory_state.end()) {
        if (it2->second->evaluate_conditions(*current_state.dlplan).empty()) {
            return std::make_tuple(false, ExtendedState(), mimir::planners::IWSearchStatistics());
        }

        auto iw_search = make_unique<mimir::planners::IWSearch>(
            problem,
            instance_info,
            successor_generator,
            max_arity);

        std::cout << step << ". Apply search rule ";
        std::shared_ptr<const dlplan::policy::Rule> reason;
        mimir::formalism::ActionList partial_plan;
        ExtendedState successor_state;
        bool partial_solution_found = iw_search->find_plan(
            it2->second,
            current_state,
            successor_state,
            partial_plan,
            reason);
        mimir::planners::IWSearchStatistics statistics = iw_search->statistics;
        std::cout << std::endl;

        if (!partial_solution_found) {
            return std::make_tuple(false, ExtendedState(), mimir::planners::IWSearchStatistics());
        } else {
            plan.insert(plan.end(), partial_plan.begin(), partial_plan.end());
            std::cout << "  Partial plan:" << std::endl;
            for (const auto& action : partial_plan) {
                std::cout << "    " << action << std::endl;
            }
        }

        if (!reason) {
            throw std::runtime_error("There should be a reason to reach a goal");
        }
        successor_state.memory = m_search_rule_by_rule_by_memory_state.at(current_state.memory).at(reason)->get_memory_state_effect();
        std::cout << "  Reason " << m_search_rule_by_rule_by_memory_state.at(current_state.memory).at(reason)->compute_signature() << std::endl;
        std::cout << "  Set current memory state to " << successor_state.memory->compute_signature() << std::endl;

        return std::make_tuple(true, successor_state, statistics);
    }
    // cout << "No applicable search rule in memory state " << current_state.memory->compute_signature() << endl;
    return std::make_tuple(false, ExtendedState(), mimir::planners::IWSearchStatistics());  // unsolved
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
            0,
            instance_info,
            atom_registry.convert_state(current_state),
            std::make_shared<dlplan::core::StateExtension>(
                register_contents,
                std::vector<dlplan::core::ConceptDenotation>{},  // no arguments since it is not wrapped into a module
                std::vector<dlplan::core::RoleDenotation>{})
        );
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

const MemoryState& ExtendedSketchImpl::get_initial_memory_state() const {
    return m_initial_memory_state;
}

const std::unordered_map<Concept, int>& ExtendedSketchImpl::get_register_mapping() const {
    return m_register_mapping;
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
    for (const auto& pair : m_register_mapping) {
        ss << pair.first->str() << " ";
    }
    ss << ")\n";  // register
    ss << "(:booleans ";
    for (const auto& pair : m_booleans) {
        ss << "(" << pair.first << " \"" << pair.second->get_element()->str() << "\") ";
    }
    ss << ")\n";  // booleans
    ss << "(:numericals ";
    for (const auto& pair : m_numericals) {
        ss << "(" << pair.first << " \"" << pair.second->get_element()->str() << "\") ";
    }
    ss << ")\n";  // numericals
    ss << "(:concepts ";
    for (const auto& pair : m_concepts) {
        ss << "(" << pair.first << " \"" << pair.second->get_element()->str() << "\") ";
    }
    ss << ")\n";  // concepts
    ss << "(:roles ";
    for (const auto& pair : m_roles) {
        ss << "(" << pair.first << " \"" << pair.second->get_element()->str() << "\") ";
    }
    ss << ")\n";  // roles
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
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const RoleMap& roles,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Concept, int>& register_mapping) {
    return std::make_shared<ExtendedSketchImpl>(
        memory_states, initial_memory_state,
        booleans, numericals, concepts, roles,
        load_rules, call_rules, action_rules, search_rules,
        sketches_by_memory_state, search_rule_by_rule_by_memory_state,
        load_rules_by_memory_state, register_mapping);
}

}