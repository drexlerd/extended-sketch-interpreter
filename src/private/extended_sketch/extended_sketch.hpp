#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"


namespace mimir::extended_sketch {

class ExtendedSketchImpl {
private:
    MemoryStateMap m_memory_states;
    MemoryState m_initial_memory_state;

    RegisterMap m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_search_rules;

public:
    ExtendedSketchImpl(
        const MemoryStateMap& memory_states,
        const MemoryState& initial_memory_state,
        const RegisterMap& registers,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const LoadRuleList& load_rules,
        const CallRuleList& call_rules,
        const ActionRuleList& action_rules,
        const SearchRuleList& search_rules);

    const MemoryState& get_initial_memory_state() const;
    const RegisterMap& get_registers() const;

    const LoadRuleList& get_load_rules() const;
    const CallRuleList& get_call_rules() const;
    const ActionRuleList& get_action_rules() const;
    const SearchRuleList& get_search_rules() const;

    std::string compute_signature() const;
};

extern ExtendedSketch make_extended_sketch(
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const RegisterMap& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules);

}

#endif