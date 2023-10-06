#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <vector>

#include "declarations.hpp"

namespace sketches::extended_sketch {
class ExtendedSketchImpl {
private:
    MemoryStateList m_memory_states;

    RegisterList m_registers;

    BooleanList m_booleans;
    NumericalList m_numericals;
    ConceptList m_concepts;

    MemoryState m_initial_memory_state;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    IWSearchRuleList m_iwsearch_rules;

public:
    ExtendedSketchImpl(
        MemoryStateList&& memory_states,
        RegisterList&& registers,
        BooleanList&& booleans,
        NumericalList&& numericals,
        ConceptList&& concepts,
        MemoryState&& initial_memory_state,
        LoadRuleList&& load_rules,
        CallRuleList&& call_rules,
        ActionRuleList&& action_rules,
        IWSearchRuleList&& iwsearch_rules);

    /// INTERNAL MEMORY RULES ///

    /// @brief Returns applicable load rule given extended state with internal memory state.
    /// @param state
    /// @return
    LoadRule find_applicable_load_rule(const ExtendedState& state) const;

    /// @brief Returns applicable call rule given extended state with internal memory state.
    /// @param state
    /// @return
    CallRule find_applicable_call_rule(const ExtendedState& state) const;

    /// EXTERNAL MEMORY RULES ///

    /// @brief Returns compatible action rule given extended state with external memory state.
    /// @param state
    /// @return
    ActionRule find_compatible_action_rule(const ExtendedState& state) const;

    /// @brief Returns compatible iwsearch rule given extended source and targets states with external memory state.
    /// @param source
    /// @param target
    /// @return
    ActionRule find_compatible_iwsearch_rule(const ExtendedState& source, const ExtendedState& target) const;
};

}

#endif
