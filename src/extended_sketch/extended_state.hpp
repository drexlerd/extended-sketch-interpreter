#ifndef SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "../external/mimir/formalism/state.hpp"
#include "../external/dlplan/include/dlplan/core.h"

namespace sketches::extended_sketch {
struct ExtendedStateImpl {
    mimir::formalism::State mimir_state;
    dlplan::core::State dlplan_state;
};

}

#endif
