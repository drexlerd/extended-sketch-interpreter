#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "../formalism/declarations.hpp"
#include "../dlplan/include/dlplan/core.h"
#include "declarations.hpp"


namespace mimir::extended_sketch {
struct ExtendedState {
    MemoryState memory;
    mimir::formalism::State mimir;
    std::shared_ptr<const dlplan::core::State> dlplan;
    // register contents are stored within dlplan state since it used it for evaluation
};

}

#endif
