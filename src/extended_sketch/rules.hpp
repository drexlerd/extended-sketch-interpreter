#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"


namespace sketches::extended_sketch {

class ExtendedRuleImpl {
protected:
    MemoryState m_condition_memory_state;
    MemoryState m_effect_memory_state;

public:
    ExtendedRuleImpl(
        const MemoryState& condition_memory_state,
        const MemoryState& effect_memory_state);
    virtual ~ExtendedRuleImpl();

    virtual int compute_evaluate_time_score() const = 0;
    std::string compute_repr() const;
    virtual void compute_repr(std::stringstream& out) const = 0;

    const MemoryState& get_condition_memory_state() const;
    const MemoryState& get_effect_memory_state() const;
};

class LoadRuleImpl : public ExtendedRuleImpl {
public:
    ~LoadRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class CallRuleImpl : public ExtendedRuleImpl {
public:
    ~CallRuleImpl() override;

    int compute_evaluate_time_score() const override;
    void compute_repr(std::stringstream& out) const override;
};

class ActionRuleImpl : public ExtendedRuleImpl {
public:
    ~ActionRuleImpl() override;

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
