#ifndef SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_
#define SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_

#include <string>

#include "declarations.hpp"


namespace mimir::extended_sketch {
struct MemoryStateImpl {
    std::string name;

    MemoryStateImpl(const std::string& name);

    std::string compute_signature() const;
};

extern MemoryState make_memory_state(const std::string& name);

}

#endif
