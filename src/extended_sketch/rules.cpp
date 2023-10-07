#include "rules.hpp"

#include <sstream>

namespace sketches::extended_sketch {

ExtendedRuleImpl::ExtendedRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& conditions)
    : m_condition_memory_state(condition_memory_state),
      m_effect_memory_state(effect_memory_state),
      m_conditions(conditions) { }

ExtendedRuleImpl::~ExtendedRuleImpl() = default;

std::string ExtendedRuleImpl::compute_repr() const {
    std::stringstream ss;
    compute_repr(ss);
    return ss.str();
}

const MemoryState& ExtendedRuleImpl::get_condition_memory_state() const {
    return m_condition_memory_state;
}

const MemoryState& ExtendedRuleImpl::get_effect_memory_state() const {
    return m_effect_memory_state;
}

const ConditionSet& ExtendedRuleImpl::get_conditions() const {
    return m_conditions;
}

}