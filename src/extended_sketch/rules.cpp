#include "rules.hpp"

#include <sstream>

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "symbol_table.hpp"


namespace sketches::extended_sketch {

ExtendedRule::ExtendedRule(
    const SymbolTable& symbol_table,
    const Handle<MemoryState>& memory_state_condition,
    const Handle<MemoryState>& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : m_symbol_table(&symbol_table),
      m_memory_state_condition(memory_state_condition),
      m_memory_state_effect(memory_state_effect),
      m_feature_conditions(feature_conditions),
      m_feature_effects(feature_effects) { }

ExtendedRule::~ExtendedRule() = default;

std::string ExtendedRule::compute_signature() const {
    std::stringstream ss;
    compute_signature(ss);
    return ss.str();
}

const Handle<MemoryState>& ExtendedRule::get_memory_state_condition() const {
    return m_memory_state_condition;
}

const Handle<MemoryState>& ExtendedRule::get_memory_state_effect() const {
    return m_memory_state_effect;
}

const ConditionSet& ExtendedRule::get_feature_conditions() const {
    return m_feature_conditions;
}

const EffectSet& ExtendedRule::get_feature_effects() const {
    return m_feature_effects;
}


LoadRule::LoadRule(
    const SymbolTable& symbol_table,
    const Handle<MemoryState>& condition_memory_state,
    const Handle<MemoryState>& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Handle<Register>& reg,
    const Concept& concept)
    : ExtendedRule(symbol_table, condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_register(reg), m_concept(concept) { }

LoadRule::~LoadRule() = default;

void LoadRule::compute_signature(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_effect].name << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << "(:load " << m_symbol_table->registers[m_register].name << " " << m_concept->get_key() << ")";
    out << ")";  // effects
    out << ")";  // rule
}


CallRule::CallRule(
    const SymbolTable& symbol_table,
    const Handle<MemoryState>& condition_memory_state,
    const Handle<MemoryState>& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Call& call)
    : ExtendedRule(symbol_table, condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_call(call) { }

CallRule::~CallRule() = default;

void CallRule::compute_signature(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_effect].name << ")";
    out << "(:call " << m_call.compute_signature() << ")";
    out << ")";  // effects
    out << ")";  // rule
}


ActionRule::ActionRule(
    const SymbolTable& symbol_table,
    const Handle<MemoryState>& memory_state_condition,
    const Handle<MemoryState>& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const std::vector<Handle<Register>>& arguments)
    : ExtendedRule(symbol_table, memory_state_condition, memory_state_effect, feature_conditions, feature_effects),
      m_action_schema(action_schema),
      m_arguments(arguments) { }

ActionRule::~ActionRule() = default;

void ActionRule::compute_signature(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_effect].name << ")";
    out << "(:action_name " << m_action_schema->name << ")";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << m_symbol_table->registers[argument].name << " ";
    }
    out << ")";  // registers
    out << ")";  // effects
    out << ")";  // rule
}


SearchRule::SearchRule(
    const SymbolTable& symbol_table,
    const Handle<MemoryState>& memory_state_condition,
    const Handle<MemoryState>& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRule(symbol_table, memory_state_condition, memory_state_effect, feature_conditions, feature_effects) { }

SearchRule::~SearchRule() = default;

void SearchRule::compute_signature(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table->memory_states[m_memory_state_effect].name << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << ")";  // effects
    out << ")";  // rule
}

}