#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "src/private/formalism/declarations.hpp"
#include "declarations.hpp"


namespace mimir::extended_sketch {
struct ExtendedStateImpl {
    MemoryState memory_state;

    mimir::formalism::State mimir_state;
};

// TODO: need extended state for evaluation in dlplan.

}

#endif
