#include "rules.hpp"

#include <sstream>

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"


namespace mimir::extended_sketch {

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

std::string ExtendedRuleImpl::compute_signature() const {
    std::stringstream ss;
    compute_signature(ss);
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

void LoadRuleImpl::apply(
    const dlplan::core::State& current_state,
    const std::unordered_map<Register, int>& register_mapping,
    dlplan::core::DenotationsCaches& denotation_caches,
    std::vector<int>& register_contents,
    MemoryState& current_memory_state) {
    const auto denotation = m_concept->get_concept()->evaluate(current_state, denotation_caches);
    if (denotation->size() == 0) {
        throw std::runtime_error("Tried to load object from empty concept into register");
    }
    int object_index = denotation->to_sorted_vector().front();
    register_contents[register_mapping.at(m_register)] = object_index;
    current_memory_state = get_memory_state_effect();
    const std::string& object_name = current_state.get_instance_info()->get_objects()[object_index].get_name();
    std::cout << "  Set content of register " << m_register->compute_signature() << " to object " << object_name << std::endl;
    std::cout << "  Set current memory state to " << get_memory_state_effect()->compute_signature() << std::endl;
}

void LoadRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:load_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str();
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    for (const auto& effect : m_feature_effects) {
        out << effect->str();
    }
    out << "(:load " << m_register->name << " " << m_concept->get_key() << ") ";
    out << ") ";  // effects
    out << ")";  // rule
}

LoadRule make_load_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept) {
    return std::make_shared<LoadRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        reg, concept);
}


CallRuleImpl::CallRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Call& call)
    : ExtendedRuleImpl(condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_call(call),
      callee() { }

CallRuleImpl::~CallRuleImpl() = default;

void CallRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:call_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str();
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    out << "(:call " << m_call.compute_signature() << ") ";
    out << ") ";  // effects
    out << ")";  // rule
}

CallRule make_call_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Call& call) {
    return std::make_shared<CallRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        call);
}


ActionRuleImpl::ActionRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const std::vector<Register>& arguments)
    : ExtendedRuleImpl( memory_state_condition, memory_state_effect, feature_conditions, feature_effects),
      m_action_schema(action_schema),
      m_arguments(arguments) { }

ActionRuleImpl::~ActionRuleImpl() = default;

void ActionRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:action_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str();
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    out << "(:action_name " << m_action_schema->name << ") ";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << argument->name << " ";
    }
    out << ")";  // registers
    out << ") ";  // effects
    out << ")";  // rule
}

ActionRule make_action_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const std::vector<Register>& arguments) {
    return std::make_shared<ActionRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        action_schema, arguments);
}


SearchRuleImpl::SearchRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions, feature_effects) { }

SearchRuleImpl::~SearchRuleImpl() = default;

void SearchRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:search_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str();
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    for (const auto& effect : m_feature_effects) {
        out << effect->str();
    }
    out << ") ";  // effects
    out << ")";  // rule
}

SearchRule make_search_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects) {
    return std::make_shared<SearchRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects);
}

}