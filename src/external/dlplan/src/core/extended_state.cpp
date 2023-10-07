#include "../../include/dlplan/core.h"


namespace dlplan::core {

ExtendedState::ExtendedState(
    std::shared_ptr<const State> state,
    ObjectIndices&& register_contents)
    : m_state(state),
      m_register_contents(std::move(register_contents)) { }

std::shared_ptr<const State> ExtendedState::get_state() const {
    return m_state;
}

const ObjectIndices& ExtendedState::get_register_contents() const {
    return m_register_contents;
}

}