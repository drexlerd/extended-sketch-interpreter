#include "rules.hpp"

#include <sstream>

namespace sketches::extended_sketch {

ExtendedRuleImpl::ExtendedRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions)
    : m_memory_state_condition(memory_state_condition),
      m_memory_state_effect(memory_state_effect),
      m_feature_conditions(feature_conditions) { }

ExtendedRuleImpl::~ExtendedRuleImpl() = default;

std::string ExtendedRuleImpl::compute_repr() const {
    std::stringstream ss;
    compute_repr(ss);
    return ss.str();
}

const MemoryState& ExtendedRuleImpl::get_memory_state_condition() const {
    return m_memory_state_condition;
}

const MemoryState& ExtendedRuleImpl::get_memory_state_effect() const {
    return m_memory_state_effect;
}

const ConditionSet& ExtendedRuleImpl::get_feature_conditions() const {
    return m_feature_conditions;
}


ActionRuleImpl::ActionRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterList& arguments)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions),
      m_action_schema(action_schema),
      m_arguments(arguments) { }

ActionRuleImpl::~ActionRuleImpl() = default;


IWSearchRuleImpl::IWSearchRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions),
      m_feature_effects(feature_effects) { }

IWSearchRuleImpl::~IWSearchRuleImpl() = default;

int IWSearchRuleImpl::compute_evaluate_time_score() const {
    // TODO
}

void IWSearchRuleImpl::compute_repr(std::stringstream& out) const {
    // TODO
}

std::shared_ptr<IWSearchRuleImpl> make_iwsearch_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects) {
    return std::make_shared<IWSearchRuleImpl>(memory_state_condition, memory_state_effect, feature_conditions, feature_effects);
}

}