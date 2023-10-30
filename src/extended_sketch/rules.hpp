#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "src/external/mimir-iw/src/private/formalism/action_schema.hpp"

#include "symbol_factory.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "call.hpp"


namespace sketches::extended_sketch {
class SymbolTable;


class ExtendedRule {
protected:
    SymbolTable const* m_symbol_table;
    Handle<MemoryState> m_memory_state_condition;
    Handle<MemoryState> m_memory_state_effect;
    ConditionSet m_feature_conditions;
    EffectSet m_feature_effects;

    ExtendedRule(
        const SymbolTable& symbol_table,
        const Handle<MemoryState>& memory_state_condition,
        const Handle<MemoryState>& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    virtual ~ExtendedRule();

    std::string compute_signature() const;
    virtual void compute_signature(std::stringstream& out) const = 0;

    const Handle<MemoryState>& get_memory_state_condition() const;
    const Handle<MemoryState>& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
    const EffectSet& get_feature_effects() const;
};

class LoadRule : public ExtendedRule {
public:
    Handle<Register> m_register;
    Concept m_concept;

    using ExtendedRule::compute_signature;

    LoadRule(
        const SymbolTable& symbol_table,
        const Handle<MemoryState>& condition_memory_state,
        const Handle<MemoryState>& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const Handle<Register>& reg,
        const Concept& concept);
    ~LoadRule() override;

    void compute_signature(std::stringstream& out) const override;
};

class CallRule : public ExtendedRule {
public:
    Call m_call;

    using ExtendedRule::compute_signature;

    CallRule(
        const SymbolTable& symbol_table,
        const Handle<MemoryState>& condition_memory_state,
        const Handle<MemoryState>& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const Call& call);
    ~CallRule() override;

    void compute_signature(std::stringstream& out) const override;
};

class ActionRule : public ExtendedRule {
public:
    mimir::formalism::ActionSchema m_action_schema;
    std::vector<Handle<Register>> m_arguments;

    using ExtendedRule::compute_signature;

    ActionRule(
        const SymbolTable& symbol_table,
        const Handle<MemoryState>& memory_state_condition,
        const Handle<MemoryState>& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const mimir::formalism::ActionSchema& action_schema,
        const std::vector<Handle<Register>>& arguments);
    ~ActionRule() override;

    void compute_signature(std::stringstream& out) const override;
};

class SearchRule : public ExtendedRule {
public:
    using ExtendedRule::compute_signature;

    SearchRule(
        const SymbolTable& symbol_table,
        const Handle<MemoryState>& memory_state_condition,
        const Handle<MemoryState>& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    ~SearchRule() override;

    void compute_signature(std::stringstream& out) const override;
};

}

#endif
