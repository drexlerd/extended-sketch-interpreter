#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "src/private/formalism/declarations.hpp"
#include "src/private/dlplan/include/dlplan/core.h"
#include "declarations.hpp"


namespace mimir::extended_sketch {
struct ExtendedState {
    MemoryState memory_state;
    mimir::formalism::State mimir_state;
    std::shared_ptr<const dlplan::core::State> dlplan_state;
    // register contents are stored within dlplan state since it used it for evaluation
};

}

#endif
