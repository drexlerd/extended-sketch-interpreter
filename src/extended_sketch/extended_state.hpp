#ifndef SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "declarations.hpp"

#include "src/external/mimir-iw/src/private/formalism/state.hpp"


namespace sketches::extended_sketch {
struct ExtendedStateImpl {
    MemoryState memory_state;

    mimir::formalism::State mimir_state;
};

// TODO: need extended state for evaluation in dlplan.

}

#endif
