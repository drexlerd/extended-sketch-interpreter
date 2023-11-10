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

    // For more convenient access.
    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> m_sketches_by_memory_state;
    std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, MemoryState> m_rule_to_memory_effect;
    std::unordered_map<MemoryState, std::vector<LoadRule>> m_load_rules_by_memory_state;
    std::unordered_map<Register, int> m_register_mapping;

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
        const SearchRuleList& search_rules,
        const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
        const std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, MemoryState>& rule_to_memory_effect,
        const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
        const std::unordered_map<Register, int>& register_mapping);

    const MemoryState& get_initial_memory_state() const;
    const RegisterMap& get_registers() const;

    const LoadRuleList& get_load_rules() const;
    const CallRuleList& get_call_rules() const;
    const ActionRuleList& get_action_rules() const;
    const SearchRuleList& get_search_rules() const;

    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& get_sketches_by_memory_state() const;
    const std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, MemoryState>& get_rule_to_memory_effect() const;
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& get_load_rules_by_memory_state() const;
    const std::unordered_map<Register, int>& get_register_mapping() const;

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
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, MemoryState>& rule_to_memory_effect,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Register, int>& register_mapping);

}

#endif
