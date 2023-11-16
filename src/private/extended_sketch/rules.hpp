#ifndef SRC_PRIVATE_EXTENDED_SKETCH_RULES_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "../formalism/action_schema.hpp"

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "action_call.hpp"
#include "module_call.hpp"


namespace mimir::extended_sketch {

class ExtendedRuleImpl {
protected:
    MemoryState m_memory_state_condition;
    MemoryState m_memory_state_effect;
    ConditionSet m_feature_conditions;
    EffectSet m_feature_effects;

    ExtendedRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    virtual ~ExtendedRuleImpl();

    bool evaluate_conditions(const ExtendedState& state) const;

    std::string compute_signature() const;
    virtual void compute_signature(std::stringstream& out) const = 0;

    const MemoryState& get_memory_state_condition() const;
    const MemoryState& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
    const EffectSet& get_feature_effects() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
public:
    Concept m_register;
    Concept m_concept;

    using ExtendedRuleImpl::evaluate_conditions;

    using ExtendedRuleImpl::compute_signature;
    using ExtendedRuleImpl::get_memory_state_condition;
    using ExtendedRuleImpl::get_memory_state_effect;
    using ExtendedRuleImpl::get_feature_conditions;
    using ExtendedRuleImpl::get_feature_effects;

    LoadRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const Concept& reg,
        const Concept& concept);
    ~LoadRuleImpl() override;

    void apply(
        const ExtendedState& current_state,
        const std::unordered_map<Concept,int>& register_mapping,
        ExtendedState& successor_state);

    void compute_signature(std::stringstream& out) const override;
};

extern LoadRule make_load_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Concept& reg,
    const Concept& concept);


class CallRuleImpl : public ExtendedRuleImpl {
public:
    ModuleCall m_call;

    std::weak_ptr<ModuleImpl> m_callee;

    using ExtendedRuleImpl::evaluate_conditions;

    using ExtendedRuleImpl::compute_signature;
    using ExtendedRuleImpl::get_memory_state_condition;
    using ExtendedRuleImpl::get_memory_state_effect;
    using ExtendedRuleImpl::get_feature_conditions;
    using ExtendedRuleImpl::get_feature_effects;

    CallRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const ModuleCall& call);
    ~CallRuleImpl() override;

    void apply(
        const ExtendedState& current_state,
        ExtendedState& successor_state,
        Module& callee,
        ExtendedState& callee_state);

    const ModuleCall& get_call() const;
    void set_callee(const Module& module);

    void compute_signature(std::stringstream& out) const override;
};

extern CallRule make_call_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ModuleCall& call);


class ActionRuleImpl : public ExtendedRuleImpl {
public:
    ActionCall m_call;

    using ExtendedRuleImpl::evaluate_conditions;

    using ExtendedRuleImpl::compute_signature;
    using ExtendedRuleImpl::get_memory_state_condition;
    using ExtendedRuleImpl::get_memory_state_effect;
    using ExtendedRuleImpl::get_feature_conditions;
    using ExtendedRuleImpl::get_feature_effects;

    ActionRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const ActionCall& call);
    ~ActionRuleImpl() override;

    void compute_signature(std::stringstream& out) const override;
};

extern ActionRule make_action_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ActionCall& call);


struct SearchRuleResult {
    bool solution_found;

};


class SearchRuleImpl : public ExtendedRuleImpl {
public:
    using ExtendedRuleImpl::evaluate_conditions;

    using ExtendedRuleImpl::compute_signature;
    using ExtendedRuleImpl::get_memory_state_condition;
    using ExtendedRuleImpl::get_memory_state_effect;
    using ExtendedRuleImpl::get_feature_conditions;
    using ExtendedRuleImpl::get_feature_effects;

    SearchRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    ~SearchRuleImpl() override;

    void compute_signature(std::stringstream& out) const override;
};

extern SearchRule make_search_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects);

}

#endif
