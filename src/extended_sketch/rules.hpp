#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "../external/mimir/formalism/action_schema.hpp"


namespace sketches::extended_sketch {

class ExtendedRuleImpl {
protected:
    // complete conditions.
    MemoryState m_memory_state_condition;
    ConditionSet m_feature_conditions;

    // partial effects.
    MemoryState m_memory_state_effect;

public:
    ExtendedRuleImpl(
        const MemoryState& memory_state_condition,
        const ConditionSet& feature_conditions,
        const MemoryState& memory_state_effect);
    virtual ~ExtendedRuleImpl();

    bool evaluate_conditions(const ExtendedState& state) const;

    virtual int compute_evaluate_time_score() const = 0;
    std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryState& get_memory_state_condition() const;
    const MemoryState& get_memory_state_effect() const;
    const ConditionSet& get_feature_conditions() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
private:
    // LoadEffect = register + concept
public:
    LoadRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& conditions
        /* load effect*/);
    ~LoadRuleImpl() override;

    /// @brief Computes the successor state when applying the rule in the given state.
    ExtendedState apply(const ExtendedState& state);

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class CallRuleImpl : public ExtendedRuleImpl {
private:
    ExtendedSketch m_extended_sketch;

public:
    CallRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& conditions
        /* call effect*/);
    ~CallRuleImpl() override;

    /// @brief Calls the extended sketch.
    ExtendedState apply(const ExtendedState& state);

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class ActionRuleImpl : public ExtendedRuleImpl {
protected:
    mimir::formalism::ActionSchema m_action_schema;
    RegisterList m_arguments;

public:
    ActionRuleImpl(
        const MemoryState& memory_state_condition,
        const ConditionSet& feature_conditions,
        const MemoryState& memory_state_effect,
        const mimir::formalism::ActionSchema& action_schema,
        const RegisterList& arguments);
    ~ActionRuleImpl() override;

    /// @brief Computes a ground action and applies it
    ExtendedState apply(const ExtendedState& state);

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class IWSearchRuleImpl : public ExtendedRuleImpl {
protected:
    EffectSet m_feature_effects;

public:
    IWSearchRuleImpl(
        const MemoryState& memory_state_condition,
        const ConditionSet& feature_conditions,
        const MemoryState& memory_state_effect,
        const EffectSet& feature_effects);
    ~IWSearchRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

extern std::shared_ptr<IWSearchRuleImpl> make_iwsearch_rule(
    const MemoryState& memory_state_condition,
    const ConditionSet& feature_conditions,
    const MemoryState& memory_state_effect,
    const EffectSet& feature_effects);

}

#endif
