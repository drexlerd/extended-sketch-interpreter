#if !defined(PLANNERS_STATE_DATA_HPP_)
#define PLANNERS_STATE_DATA_HPP_

#include "../formalism/problem.hpp"

#include <vector>


namespace planners {
    struct StateData {
        formalism::State state;
        std::vector<int> state_atom_indices;
        uint32_t state_index;
    };
}

#endif