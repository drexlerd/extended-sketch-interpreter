#ifndef SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_EXTENDED_STATE_HPP_

#include "src/private/formalism/declarations.hpp"
#include "src/private/dlplan/include/dlplan/core.h"
#include "declarations.hpp"


namespace mimir::extended_sketch {
struct ExtendedState {
    MemoryState memory;
    mimir::formalism::State mimir;
    std::shared_ptr<const dlplan::core::State> dlplan;
    // register contents are stored within dlplan state since it used it for evaluation
};

extern ExtendedState create_initial_state(
    const mimir::formalism::ProblemDescription& problem,
    const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
    const MemoryState& current_memory_state,
    int num_registers);

}

#endif
