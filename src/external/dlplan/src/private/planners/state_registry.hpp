#if !defined(PLANNERS_STATE_REGISTRY_HPP_)
#define PLANNERS_STATE_REGISTRY_HPP_

#include "../formalism/action.hpp"
#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"

#include <unordered_map>
#include <vector>


namespace planners {
    class StateRegistry {
        std::unordered_map<formalism::State, uint32_t> state_to_index_;
        std::vector<formalism::State> state_by_index_;

        public:
            formalism::State lookup_state(uint32_t state_index) const;

            uint32_t find_state(formalism::State state) const;

            uint32_t register_state(formalism::State state);

            static const uint32_t no_state;
    };
}

#endif