#include "memory_state.hpp"


namespace sketches::extended_sketch {

MemoryStateImpl::MemoryStateImpl(const std::string& key)
    : m_key(key) { }

const std::string& MemoryStateImpl::get_key() const {
    return m_key;
}

std::shared_ptr<MemoryStateImpl> make_memory_state(const std::string& key) {
    return std::make_shared<MemoryStateImpl>(key);
}

}
