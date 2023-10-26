#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "src/external/mimir-iw/src/private/formalism/action_schema.hpp"

#include "symbol_factory.hpp"
#include "memory_state.hpp"
#include "register.hpp"


namespace sketches::extended_sketch {
class SymbolTable;

struct LoadRule;
using LoadRuleHandle = SymbolHandle<LoadRule>;
using LoadRuleHandleList = std::vector<LoadRuleHandle>;

struct CallRule;
using CallRuleHandle = SymbolHandle<CallRule>;
using CallRuleHandleList = std::vector<CallRuleHandle>;

struct ActionRule;
using ActionRuleHandle = SymbolHandle<ActionRule>;
using ActionRuleHandleList = std::vector<ActionRuleHandle>;

struct SearchRule;
using SearchRuleHandle = SymbolHandle<SearchRule>;
using SearchRuleHandleList = std::vector<SearchRuleHandle>;


class ExtendedRule {
public:
    SymbolTable& m_symbol_table;
    MemoryStateHandle m_memory_state_condition;
    MemoryStateHandle m_memory_state_effect;
    ConditionSet m_feature_conditions;
    EffectSet m_feature_effects;

    ExtendedRule(
        SymbolTable& symbol_table,
        const MemoryStateHandle& memory_state_condition,
        const MemoryStateHandle& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    virtual ~ExtendedRule();

    bool evaluate_conditions(const ExtendedState& state) const;

    virtual int compute_evaluate_time_score() const;
    virtual std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryStateHandle& get_memory_state_condition() const;
    const MemoryStateHandle& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
    const EffectSet& get_feature_effects() const;
};

class LoadRule : public ExtendedRule {
public:
    RegisterHandle m_register;
    Concept m_concept;

    using ExtendedRule::compute_repr;

    LoadRule(
        SymbolTable& symbol_table,
        const MemoryStateHandle& condition_memory_state,
        const MemoryStateHandle& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const RegisterHandle& reg,
        const Concept& concept);
    ~LoadRule() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class CallRule : public ExtendedRule {
public:
    std::string m_extended_sketch_name;
    RegisterHandleList m_arguments;

    using ExtendedRule::compute_repr;

    CallRule(
        SymbolTable& symbol_table,
        const MemoryStateHandle& condition_memory_state,
        const MemoryStateHandle& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const std::string& extended_sketch_name,
        const RegisterHandleList& arguments);
    ~CallRule() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class ActionRule : public ExtendedRule {
public:
    mimir::formalism::ActionSchema m_action_schema;
    RegisterHandleList m_arguments;

    using ExtendedRule::compute_repr;

    ActionRule(
        SymbolTable& symbol_table,
        const MemoryStateHandle& memory_state_condition,
        const MemoryStateHandle& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const mimir::formalism::ActionSchema& action_schema,
        const RegisterHandleList& arguments);
    ~ActionRule() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class SearchRule : public ExtendedRule, public Symbol {
public:
    using ExtendedRule::compute_repr;

    SearchRule(
        SymbolTable& symbol_table,
        const MemoryStateHandle& memory_state_condition,
        const MemoryStateHandle& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    ~SearchRule() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};


class LoadRuleFactory : public SymbolFactory<LoadRule> {
};

class CallRuleFactory : public SymbolFactory<CallRule> {
};

class ActionRuleFactory : public SymbolFactory<ActionRule> {
};

class SearchRuleFactory : public SymbolFactory<SearchRule> {
};


}

#endif
