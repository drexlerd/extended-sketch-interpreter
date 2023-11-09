#if !defined(PLANNERS_STATE_DATA_HPP_)
#define PLANNERS_STATE_DATA_HPP_

#include "../formalism/problem.hpp"
#include "../extended_sketch/declarations.hpp"
#include "../extended_sketch/extended_state.hpp"


#include <vector>


namespace mimir::planners {
    struct StateData {
        uint32_t state_index;
        mimir::extended_sketch::ExtendedState extended_state;
    };
}

#endif