#ifndef SRC_PRIVATE_EXTENDED_SKETCH_RULES_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "../formalism/action_schema.hpp"

#include "extended_state.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "call.hpp"


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

    std::string compute_signature() const;
    virtual void compute_signature(std::stringstream& out) const = 0;

    const MemoryState& get_memory_state_condition() const;
    const MemoryState& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
    const EffectSet& get_feature_effects() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
public:
    Register m_register;
    Concept m_concept;

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
        const Register& reg,
        const Concept& concept);
    ~LoadRuleImpl() override;

    void apply(
        const ExtendedState& current_state,
        const std::unordered_map<Register,int>& register_mapping,
        ExtendedState& successor_state);

    void compute_signature(std::stringstream& out) const override;
};

extern LoadRule make_load_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept);


class CallRuleImpl : public ExtendedRuleImpl {
public:
    Call m_call;

    class ExtendedSketchImpl;
    std::weak_ptr<ExtendedSketchImpl> callee;

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
        const Call& call);
    ~CallRuleImpl() override;

    void compute_signature(std::stringstream& out) const override;
};

extern CallRule make_call_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Call& call);


class ActionRuleImpl : public ExtendedRuleImpl {
public:
    mimir::formalism::ActionSchema m_action_schema;
    std::vector<Register> m_arguments;

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
        const mimir::formalism::ActionSchema& action_schema,
        const std::vector<Register>& arguments);
    ~ActionRuleImpl() override;

    void compute_signature(std::stringstream& out) const override;
};

extern ActionRule make_action_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const mimir::formalism::ActionSchema& action_schema,
    const std::vector<Register>& arguments);


class SearchRuleImpl : public ExtendedRuleImpl {
public:
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
