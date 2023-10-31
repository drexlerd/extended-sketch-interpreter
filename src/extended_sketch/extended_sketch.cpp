#include "extended_sketch.hpp"

#include "declarations.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "rules.hpp"


namespace sketches::extended_sketch {

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
    const SearchRuleList& search_rules)
    : m_memory_states(memory_states),
      m_initial_memory_state(initial_memory_state),
      m_registers(registers),
      m_booleans(booleans),
      m_numericals(numericals),
      m_concepts(concepts),
      m_load_rules(load_rules),
      m_call_rules(call_rules),
      m_action_rules(action_rules),
      m_search_rules(search_rules) {
}

std::string ExtendedSketchImpl::compute_signature() const {
    std::stringstream ss;
    ss << "(:extended_sketch\n"
       << "(:memory_states ";
    for (const auto& pair : m_memory_states) {
        ss << pair.second->compute_signature() << " ";
    }
    ss << ")\n";  // memory_states
    ss << "(:initial_memory-state " << m_initial_memory_state->compute_signature() << ")\n";
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
    const SearchRuleList& search_rules) {
    return std::make_shared<ExtendedSketchImpl>(
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules);
}

}