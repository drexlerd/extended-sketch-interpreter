#include "extended_sketch.hpp"


namespace sketches::extended_sketch {

ExtendedSketchImpl::ExtendedSketchImpl(
    const std::string& name,
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterMap& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& iwsearch_rules)
    : m_name(name),
      m_memory_states(memory_states),
      m_initial_memory_state(initial_memory_state),
      m_registers(registers),
      m_booleans(booleans),
      m_numericals(numericals),
      m_concepts(concepts),
      m_load_rules(load_rules),
      m_call_rules(call_rules),
      m_action_rules(action_rules),
      m_iwsearch_rules(iwsearch_rules) { }

const std::string& ExtendedSketchImpl::get_name() const {
    return m_name;
}

std::shared_ptr<ExtendedSketchImpl> create_extended_sketch(
    const std::string& name,
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterMap& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& iwsearch_rules) {
    return std::make_shared<ExtendedSketchImpl>(
        name,
        memory_states,
        initial_memory_state,
        registers,
        booleans,
        numericals,
        concepts,
        load_rules,
        call_rules,
        action_rules,
        iwsearch_rules);
}

}