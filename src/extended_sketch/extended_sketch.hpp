#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"
#include "arguments.hpp"


namespace sketches::extended_sketch {
class ExtendedSketchImpl {
private:
    std::string m_name;

    MemoryStateMap m_memory_states;
    MemoryState m_initial_memory_state;

    ArgumentVariantList m_arguments;

    RegisterMap m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_iwsearch_rules;

public:
    ExtendedSketchImpl(
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
        const SearchRuleList& iwsearch_rules);

    const std::string& get_name() const;
};

extern std::shared_ptr<ExtendedSketchImpl> create_extended_sketch(
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
    const SearchRuleList& iwsearch_rules);

}

#endif
