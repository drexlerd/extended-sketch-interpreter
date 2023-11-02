#if !defined(PLANNERS_STATE_DATA_HPP_)
#define PLANNERS_STATE_DATA_HPP_

#include "../formalism/problem.hpp"
#include "src/extended_sketch/declarations.hpp"

#include <vector>


namespace mimir::planners {
    struct StateData {
        formalism::State state;
        std::vector<int> state_atom_indices;
        uint32_t state_index;
        std::vector<int> register_contents;
        sketches::extended_sketch::MemoryState memory_state;
    };
}

#endif