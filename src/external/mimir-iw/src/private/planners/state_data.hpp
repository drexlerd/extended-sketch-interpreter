#if !defined(PLANNERS_STATE_DATA_HPP_)
#define PLANNERS_STATE_DATA_HPP_

#include "../formalism/problem.hpp"
#include "src/extended_sketch/declarations.hpp"

#include <vector>


namespace mimir::planners {
    struct StateData {
        uint32_t state_index;
        formalism::State state;
        std::shared_ptr<dlplan::core::State> dlplan_state;
        sketches::extended_sketch::MemoryState memory_state;
    };
}

#endif