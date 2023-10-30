#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"


namespace sketches::extended_sketch {

class ExtendedSketchImpl {
private:
    MemoryStateList m_memory_states;
    MemoryState m_initial_memory_state;

    RegisterList m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_search_rules;

public:
    ExtendedSketchImpl(
        const MemoryStateList& memory_states,
        const MemoryState& initial_memory_state,
        const RegisterList& registers,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const LoadRuleList& load_rules,
        const CallRuleList& call_rules,
        const ActionRuleList& action_rules,
        const SearchRuleList& search_rules);

    std::string compute_signature() const;
};

extern ExtendedSketch make_extended_sketch(
    const MemoryStateList& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterList& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules);

}

#endif
