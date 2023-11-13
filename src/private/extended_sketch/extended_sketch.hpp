#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"
#include "extended_state.hpp"
#include "../planners/iw_search_statistics.hpp"
#include "../generators/successor_generator_factory.hpp"


namespace mimir::extended_sketch {

class ExtendedSketchImpl {
private:
    MemoryStateMap m_memory_states;
    MemoryState m_initial_memory_state;

    RegisterMap m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;  // TODO: add registers to concepts

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_search_rules;

    // For more convenient access.
    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> m_sketches_by_memory_state;
    std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>> m_search_rule_by_rule_by_memory_state;
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
        const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
        const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
        const std::unordered_map<Register, int>& register_mapping);

    bool try_apply_load_rule(
        const ExtendedState& current_state,
        int& step,
        ExtendedState& successor_state);

    bool try_apply_search_rule(
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
        const mimir::planners::SuccessorGenerator& successor_generator,
        int max_arity,
        const ExtendedState& current_state,
        int& step,
        ExtendedState& successor_state,
        mimir::formalism::ActionList& plan,
        mimir::planners::IWSearchStatistics& statistics);

    ExtendedState create_initial_extended_state(
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info);


    const CallRuleList& get_call_rules() const;

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
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Register, int>& register_mapping);

}

#endif
