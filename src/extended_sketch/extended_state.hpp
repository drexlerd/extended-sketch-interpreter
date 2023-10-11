#ifndef SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "declarations.hpp"

#include "../external/mimir/formalism/state.hpp"
#include "../external/dlplan/include/dlplan/core.h"

namespace sketches::extended_sketch {
struct ExtendedStateImpl {
    MemoryState memory_state;

    mimir::formalism::State mimir_state;

    dlplan::core::ExtendedState dlplan_state;
};

}

#endif
