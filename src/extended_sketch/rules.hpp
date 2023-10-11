#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "../external/mimir/formalism/action_schema.hpp"


namespace sketches::extended_sketch {

class ExtendedRuleImpl {
protected:
    MemoryState m_memory_state_condition;
    MemoryState m_memory_state_effect;
    ConditionSet m_feature_conditions;

public:
    ExtendedRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions);
    virtual ~ExtendedRuleImpl();

    bool evaluate_conditions(const ExtendedState& state) const;

    virtual int compute_evaluate_time_score() const;
    std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryState& get_memory_state_condition() const;
    const MemoryState& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
protected:
    EffectSet m_feature_effects;
    Register m_register;
    Concept m_concept;

public:
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

extern std::shared_ptr<LoadRuleImpl> create_load_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Register& reg,
    const Concept& concept);


class CallRuleImpl : public ExtendedRuleImpl {
protected:
    // Note: do we want to throw an error if a sketch does
    // not exist instead of storing a name and crashing at runtime?
    // Maybe we should do a dry parser run to read names.
    std::string m_extended_sketch_name;
    RegisterList m_arguments;

public:
    CallRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& feature_conditions,
        const std::string& extended_sketch_name,
        const RegisterList& arguments);
    ~CallRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

extern std::shared_ptr<CallRuleImpl> create_call_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const std::string& extended_sketch_name,
    const RegisterList& arguments);


class ActionRuleImpl : public ExtendedRuleImpl {
protected:
    mimir::formalism::ActionSchema m_action_schema;
    RegisterList m_arguments;

public:
    ActionRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const mimir::formalism::ActionSchema& action_schema,
        const RegisterList& arguments);
    ~ActionRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

extern std::shared_ptr<ActionRuleImpl> create_action_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const mimir::formalism::ActionSchema& action_schema,
    const RegisterList& arguments);


class IWSearchRuleImpl : public ExtendedRuleImpl {
protected:
    EffectSet m_feature_effects;

public:
    IWSearchRuleImpl(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
    ~IWSearchRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

extern std::shared_ptr<IWSearchRuleImpl> create_iwsearch_rule(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects);

}

#endif
