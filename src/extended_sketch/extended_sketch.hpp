#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"
#include "arguments.hpp"
#include "signature.hpp"
#include "register.hpp"
#include "memory_state.hpp"


namespace sketches::extended_sketch {


class ExtendedSketchImpl {
private:
    Signature m_signature;

    MemoryStateHandleList m_memory_states;
    MemoryStateHandle m_initial_memory_state;

    RegisterHandleList m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_iwsearch_rules;

public:
    ExtendedSketchImpl(
        const Signature& signature,
        const MemoryStateHandleList& memory_states,
        const MemoryStateHandle& initial_memory_state,
        const RegisterHandleList& registers,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const LoadRuleList& load_rules,
        const CallRuleList& call_rules,
        const ActionRuleList& action_rules,
        const SearchRuleList& iwsearch_rules);

    const Signature& get_signature() const;
};

extern std::shared_ptr<ExtendedSketchImpl> create_extended_sketch(
    const Signature& signature,
    const MemoryStateHandleList& memory_states,
    const MemoryStateHandle& initial_memory_state,
    const RegisterHandleList& registers,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& iwsearch_rules);

}

#endif
