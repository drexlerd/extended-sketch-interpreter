#include "memory_state.hpp"


namespace sketches::extended_sketch {

MemoryStateImpl::MemoryStateImpl(const std::string& name)
    : name(name) {
}

std::string MemoryStateImpl::compute_signature() const {
    return name;
}

MemoryState make_memory_state(const std::string& name) {
    return std::make_shared<MemoryStateImpl>(name);
}

}