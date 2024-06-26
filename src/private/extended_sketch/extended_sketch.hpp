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

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;
    RoleMap m_roles;

    LoadRuleList m_load_rules;
    CallRuleList m_call_rules;
    ActionRuleList m_action_rules;
    SearchRuleList m_search_rules;

    // For more convenient access.
    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> m_sketches_by_memory_state;
    std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>> m_search_rule_by_rule_by_memory_state;
    std::unordered_map<MemoryState, std::vector<LoadRule>> m_load_rules_by_memory_state;
    std::unordered_map<Concept, int> m_register_mapping;

public:
    ExtendedSketchImpl(
        const MemoryStateMap& memory_states,
        const MemoryState& initial_memory_state,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const RoleMap& roles,
        const LoadRuleList& load_rules,
        const CallRuleList& call_rules,
        const ActionRuleList& action_rules,
        const SearchRuleList& search_rules,
        const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
        const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
        const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
        const std::unordered_map<Concept, int>& register_mapping);

    std::tuple<bool, ExtendedState> try_apply_load_rule(
        const ExtendedState& current_state,
        int step) const;

    std::tuple<bool, ExtendedState, Module, ExtendedState> try_apply_call_rule(
        const ExtendedState& current_state,
        int step) const;

    std::tuple<bool, ExtendedState, mimir::formalism::Action> try_apply_action_rule(
        const mimir::formalism::ProblemDescription& problem,
        const ExtendedState& current_state,
        int step);

    std::tuple<bool, ExtendedState, mimir::planners::IWSearchStatistics> try_apply_search_rule(
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
        const mimir::planners::SuccessorGenerator& successor_generator,
        int max_arity,
        const ExtendedState& current_state,
        int step,
        mimir::formalism::ActionList& plan) const;

    ExtendedState create_initial_extended_state(
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info);


    const CallRuleList& get_call_rules() const;
    const MemoryState& get_initial_memory_state() const;
    const std::unordered_map<Concept, int>& get_register_mapping() const;

    std::string compute_signature() const;
};

extern ExtendedSketch make_extended_sketch(
    const MemoryStateMap& memory_states,
    const MemoryState& initial_memory_state,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts,
    const RoleMap& roles,
    const LoadRuleList& load_rules,
    const CallRuleList& call_rules,
    const ActionRuleList& action_rules,
    const SearchRuleList& search_rules,
    const std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
    const std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>>& search_rule_by_rule_by_memory_state,
    const std::unordered_map<MemoryState, std::vector<LoadRule>>& load_rules_by_memory_state,
    const std::unordered_map<Concept, int>& register_mapping);

}

#endif
