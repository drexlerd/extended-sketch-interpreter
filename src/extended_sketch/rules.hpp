#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"

#include "../external/mimir/formalism/action_schema.hpp"


namespace sketches::extended_sketch {

class ExtendedRuleImpl {
protected:
    MemoryState m_condition_memory_state;
    MemoryState m_effect_memory_state;

    ConditionSet m_conditions;

public:
    ExtendedRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& conditions);
    virtual ~ExtendedRuleImpl();

    bool evaluate_conditions(const ExtendedState& state) const;

    virtual int compute_evaluate_time_score() const = 0;
    std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryState& get_condition_memory_state() const;
    const MemoryState& get_effect_memory_state() const;
    const ConditionSet& get_conditions() const;
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
private:
    mimir::formalism::ActionSchema m_action_schema;

public:
    ActionRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state,
        const ConditionSet& conditions
        /* action rule effect*/);
    ~ActionRuleImpl() override;

    /// @brief Computes a ground action and applies it
    ExtendedState apply(const ExtendedState& state);

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class IWSearchRuleImpl : public ExtendedRuleImpl {
public:
    ~IWSearchRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};
}

#endif
