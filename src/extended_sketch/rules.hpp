#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "src/external/mimir-iw/src/private/formalism/action_schema.hpp"


namespace sketches::extended_sketch {

class ExtendedRuleImpl {
protected:
    MemoryState m_memory_state_condition;
    MemoryState m_memory_state_effect;
    ConditionSet m_feature_conditions;
    EffectSet m_feature_effects;

public:
    ExtendedRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    virtual ~ExtendedRuleImpl();

    bool evaluate_conditions(const ExtendedState& state) const;

    virtual int compute_evaluate_time_score() const;
    virtual std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryState& get_memory_state_condition() const;
    const MemoryState& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
    const EffectSet& get_feature_effects() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
protected:
    Register m_register;
    Concept m_concept;

public:
    using ExtendedRuleImpl::compute_repr;

    LoadRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const Register& reg,
        const Concept& concept);
    ~LoadRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};


class CallRuleImpl : public ExtendedRuleImpl {
protected:
    std::string m_extended_sketch_name;
    RegisterList m_arguments;

public:
    using ExtendedRuleImpl::compute_repr;

    CallRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const std::string& extended_sketch_name,
        const RegisterList& arguments);
    ~CallRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};


class ActionRuleImpl : public ExtendedRuleImpl {
protected:
    mimir::formalism::ActionSchema m_action_schema;
    RegisterList m_arguments;

public:
    using ExtendedRuleImpl::compute_repr;

    ActionRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const mimir::formalism::ActionSchema& action_schema,
        const RegisterList& arguments);
    ~ActionRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};


class SearchRuleImpl : public ExtendedRuleImpl {
public:
    using ExtendedRuleImpl::compute_repr;

    SearchRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    ~SearchRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

}

#endif
