#include "extended_sketch_factory.hpp"

#include "rules.hpp"


namespace sketches::extended_sketch {

ExtendedSketchFactory::ExtendedSketchFactory() : m_caches(Caches()) { }

LoadRule ExtendedSketchFactory::make_load_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept) {
    return m_caches.load_rules->insert(
        std::make_unique<LoadRuleImpl>(
            memory_state_condition,
            memory_state_effect,
            feature_conditions,
            feature_effects,
            reg,
            concept)).first;
}

CallRule ExtendedSketchFactory::make_call_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const std::string& extended_sketch_name,
    const RegisterList& arguments) {
    return m_caches.call_rules->insert(
        std::make_unique<CallRuleImpl>(
            memory_state_condition,
            memory_state_effect,
            feature_conditions,
            feature_effects,
            extended_sketch_name,
            arguments)).first;
}

SearchRule ExtendedSketchFactory::make_search_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects) {
    return m_caches.search_rules->insert(
        std::make_unique<SearchRuleImpl>(
            memory_state_condition,
            memory_state_effect,
            feature_conditions,
            feature_effects)).first;
}

ActionRule ExtendedSketchFactory::make_action_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterList& arguments) {
    return m_caches.action_rules->insert(
        std::make_unique<ActionRuleImpl>(
            memory_state_condition,
            memory_state_effect,
            feature_conditions,
            feature_effects,
            action_schema,
            arguments)).first;
}

}