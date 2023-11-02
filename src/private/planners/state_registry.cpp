#include "state_registry.hpp"

#include <cassert>
#include <limits>

namespace mimir::planners {

    formalism::State StateRegistry::lookup_state(uint32_t state_index) const {
        assert(state_index < state_by_index_.size());
        return state_by_index_.at(state_index);
    }

    uint32_t StateRegistry::find_state(formalism::State state) const {
        auto it = state_to_index_.find(state);
        return (it != state_to_index_.end()) ? it->second : no_state;
    }

    uint32_t StateRegistry::register_state(formalism::State state) {
        assert(find_state(state) == StateRegistry::no_state);
        int state_index = state_to_index_.size();
        state_to_index_.emplace(state, state_index);
        state_by_index_.push_back(state);
        return state_index;
    }

    const uint32_t StateRegistry::no_state = std::numeric_limits<uint32_t>::max();
}