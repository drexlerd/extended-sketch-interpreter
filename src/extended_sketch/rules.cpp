#include "rules.hpp"

#include <sstream>

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "symbol_table.hpp"


namespace sketches::extended_sketch {

ExtendedRule::ExtendedRule(
    SymbolTable& symbol_table,
    const MemoryStateHandle& memory_state_condition,
    const MemoryStateHandle& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : m_symbol_table(symbol_table),
      m_memory_state_condition(memory_state_condition),
      m_memory_state_effect(memory_state_effect),
      m_feature_conditions(feature_conditions),
      m_feature_effects(feature_effects) { }

ExtendedRule::~ExtendedRule() = default;

int ExtendedRule::compute_evaluate_time_score() const {
    int score = 0;
    for (const auto& condition : m_feature_conditions) {
        score += condition->compute_evaluate_time_score();
    }
    for (const auto& effect : m_feature_effects) {
        score += effect->compute_evaluate_time_score();
    }
    return score;
}

std::string ExtendedRule::compute_repr() const {
    std::stringstream ss;
    compute_repr(ss);
    return ss.str();
}

const MemoryStateHandle& ExtendedRule::get_memory_state_condition() const {
    return m_memory_state_condition;
}

const MemoryStateHandle& ExtendedRule::get_memory_state_effect() const {
    return m_memory_state_effect;
}

const ConditionSet& ExtendedRule::get_feature_conditions() const {
    return m_feature_conditions;
}

const EffectSet& ExtendedRule::get_feature_effects() const {
    return m_feature_effects;
}


LoadRule::LoadRule(
    SymbolTable& symbol_table,
    const MemoryStateHandle& condition_memory_state,
    const MemoryStateHandle& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const RegisterHandle& reg,
    const Concept& concept)
    : ExtendedRule(symbol_table, condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_register(reg), m_concept(concept) { }

LoadRule::~LoadRule() = default;

int LoadRule::compute_evaluate_time_score() const {
    return ExtendedRule::compute_evaluate_time_score();
}

void LoadRule::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_effect].name << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << "(:load " << m_symbol_table.registers[m_register].name << " " << m_concept->get_key() << ")";
    out << ")";  // effects
    out << ")";  // rule
}


CallRule::CallRule(
    SymbolTable& symbol_table,
    const MemoryStateHandle& condition_memory_state,
    const MemoryStateHandle& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const std::string& extended_sketch_name,
    const RegisterHandleList& arguments)
    : ExtendedRule(symbol_table, condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_extended_sketch_name(extended_sketch_name),
      m_arguments(arguments) { }

CallRule::~CallRule() = default;

int CallRule::compute_evaluate_time_score() const {
    return ExtendedRule::compute_evaluate_time_score();
}

void CallRule::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_effect].name << ")";
    out << "(:extended_sketch_name " << m_extended_sketch_name << ")";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << m_symbol_table.registers[argument].name << " ";
    }
    out << ")";  // registers
    out << ")";  // effects
    out << ")";  // rule
}


ActionRule::ActionRule(
    SymbolTable& symbol_table,
    const MemoryStateHandle& memory_state_condition,
    const MemoryStateHandle& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterHandleList& arguments)
    : ExtendedRule(symbol_table, memory_state_condition, memory_state_effect, feature_conditions, feature_effects),
      m_action_schema(action_schema),
      m_arguments(arguments) { }

ActionRule::~ActionRule() = default;

int ActionRule::compute_evaluate_time_score() const {
    return ExtendedRule::compute_evaluate_time_score();
}

void ActionRule::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_effect].name << ")";
    out << "(:action_name " << m_action_schema->name << ")";
    out << "(:registers ";
    for (const auto& argument : m_arguments) {
        out << m_symbol_table.registers[argument].name << " ";
    }
    out << ")";  // registers
    out << ")";  // effects
    out << ")";  // rule
}


SearchRule::SearchRule(
    SymbolTable& symbol_table,
    const MemoryStateHandle& memory_state_condition,
    const MemoryStateHandle& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRule(symbol_table, memory_state_condition, memory_state_effect, feature_conditions, feature_effects) { }

SearchRule::~SearchRule() = default;

int SearchRule::compute_evaluate_time_score() const {
    return ExtendedRule::compute_evaluate_time_score();
}

void SearchRule::compute_repr(std::stringstream& out) const {
    out << "(:rule "
        << "(:conditions ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_condition].name << ")";
    for (const auto& condition : m_feature_conditions) {
        out << condition->compute_repr();
    }
    out << ")";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_symbol_table.memory_states[m_memory_state_effect].name << ")";
    for (const auto& effect : m_feature_effects) {
        out << effect->compute_repr();
    }
    out << ")";  // effects
    out << ")";  // rule
}

}