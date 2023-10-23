#include "rules.hpp"

#include <sstream>

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"


namespace sketches::extended_sketch {

ExtendedRuleImpl::ExtendedRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : m_memory_state_condition(memory_state_condition),
      m_memory_state_effect(memory_state_effect),
      m_feature_conditions(feature_conditions),
      m_feature_effects(feature_effects) { }

ExtendedRuleImpl::~ExtendedRuleImpl() = default;

int ExtendedRuleImpl::compute_evaluate_time_score() const {
    int score = 0;
    for (const auto& condition : m_feature_conditions) {
        score += condition->compute_evaluate_time_score();
    }
    for (const auto& effect : m_feature_effects) {
        score += effect->compute_evaluate_time_score();
    }
    return score;
}

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

const EffectSet& ExtendedRuleImpl::get_feature_effects() const {
    return m_feature_effects;
}


LoadRuleImpl::LoadRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept)
    : ExtendedRuleImpl(condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_register(reg), m_concept(concept) { }

LoadRuleImpl::~LoadRuleImpl() = default;

int LoadRuleImpl::compute_evaluate_time_score() const {
    return ExtendedRuleImpl::compute_evaluate_time_score();
}

void LoadRuleImpl::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->get_key() << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->get_key() << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << "(:load " << m_register->get_key() << " " << m_concept->get_key() << ")";
    out << ")";  // effects
    out << ")";  // rule
}


std::shared_ptr<LoadRuleImpl> create_load_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept) {
    return std::make_shared<LoadRuleImpl>(
        memory_state_condition,
        memory_state_effect,
        feature_conditions,
        feature_effects,
        reg,
        concept);
}


CallRuleImpl::CallRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const std::string& extended_sketch_name,
    const RegisterList& arguments)
    : ExtendedRuleImpl(condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_extended_sketch_name(extended_sketch_name),
      m_arguments(arguments) { }

CallRuleImpl::~CallRuleImpl() = default;

int CallRuleImpl::compute_evaluate_time_score() const {
    return ExtendedRuleImpl::compute_evaluate_time_score();
}

void CallRuleImpl::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->get_key() << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->get_key() << ")";
    out << "(:extended_sketch_name " << m_extended_sketch_name << ")";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << argument->get_key() << " ";
    }
    out << ")";  // registers
    out << ")";  // effects
    out << ")";  // rule
}

std::shared_ptr<CallRuleImpl> create_call_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const std::string& extended_sketch_name,
    const RegisterList& arguments) {
    return std::make_shared<CallRuleImpl>(
        memory_state_condition,
        memory_state_effect,
        feature_conditions,
        feature_effects,
        extended_sketch_name,
        arguments);
}


ActionRuleImpl::ActionRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterList& arguments)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions, feature_effects),
      m_action_schema(action_schema),
      m_arguments(arguments) { }

ActionRuleImpl::~ActionRuleImpl() = default;

int ActionRuleImpl::compute_evaluate_time_score() const {
    return ExtendedRuleImpl::compute_evaluate_time_score();
}

void ActionRuleImpl::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->get_key() << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->get_key() << ")";
    out << "(:action_name " << m_action_schema->name << ")";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << argument->get_key() << " ";
    }
    out << ")";  // registers
    out << ")";  // effects
    out << ")";  // rule
}

std::shared_ptr<ActionRuleImpl> create_action_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterList& arguments) {
    return std::make_shared<ActionRuleImpl>(
        memory_state_condition,
        memory_state_effect,
        feature_conditions,
        feature_effects,
        action_schema,
        arguments);
}


SearchRuleImpl::SearchRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions, feature_effects) { }

SearchRuleImpl::~SearchRuleImpl() = default;

int SearchRuleImpl::compute_evaluate_time_score() const {
    return ExtendedRuleImpl::compute_evaluate_time_score();
}

void SearchRuleImpl::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->get_key() << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->get_key() << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << ")";  // effects
    out << ")";  // rule
}

std::shared_ptr<SearchRuleImpl> create_iwsearch_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects) {
    return std::make_shared<SearchRuleImpl>(memory_state_condition, memory_state_effect, feature_conditions, feature_effects);
}

}