#include "extended_sketch.hpp"

#include "symbol_table.hpp"


namespace sketches::extended_sketch {

ExtendedSketch::ExtendedSketch(
    const SymbolTable& parent_symbol_table,
    std::unique_ptr<const SymbolTable>&& symbol_table,
    const Signature& signature,
    const MemoryStateHandleList& memory_states,
    const MemoryStateHandle& initial_memory_state,
    const RegisterHandleList& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleHandleList& load_rules,
    const CallRuleHandleList& call_rules,
    const ActionRuleHandleList& action_rules,
    const SearchRuleHandleList& iwsearch_rules)
    : m_parent_symbol_table(&parent_symbol_table),
      m_symbol_table(std::move(symbol_table)),
      m_signature(signature),
      m_memory_states(memory_states),
      m_initial_memory_state(initial_memory_state),
      m_registers(registers),
      m_booleans(booleans),
      m_numericals(numericals),
      m_concepts(concepts),
      m_load_rules(load_rules),
      m_call_rules(call_rules),
      m_action_rules(action_rules),
      m_iwsearch_rules(iwsearch_rules) {
}

std::string ExtendedSketch::compute_signature() const {
    // TODO
    return std::string("");
}

}