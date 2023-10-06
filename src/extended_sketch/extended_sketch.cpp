#include "extended_sketch.hpp"


namespace sketches::extended_sketch {

ExtendedSketchImpl::ExtendedSketchImpl(
    MemoryStateList&& memory_states,
    RegisterList&& registers,
    BooleanList&& booleans,
    NumericalList&& numericals,
    ConceptList&& concepts,
    MemoryState&& initial_memory_state,
    LoadRuleList&& load_rules,
    CallRuleList&& call_rules,
    ActionRuleList&& action_rules,
    IWSearchRuleList&& iwsearch_rules)
    : m_memory_states(std::move(memory_states)),
      m_registers(std::move(registers)),
      m_booleans(std::move(booleans)),
      m_numericals(std::move(numericals)),
      m_concepts(std::move(concepts)),
      m_initial_memory_state(std::move(initial_memory_state)),
      m_load_rules(std::move(load_rules)),
      m_call_rules(std::move(call_rules)),
      m_action_rules(std::move(action_rules)),
      m_iwsearch_rules(std::move(iwsearch_rules)) { }

}