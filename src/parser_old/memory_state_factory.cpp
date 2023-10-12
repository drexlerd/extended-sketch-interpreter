#include "memory_state_factory.hpp"

#include "../extended_sketch/memory_state.hpp"


namespace sketches::extended_sketch {

MemoryState MemoryStateFactory::make_memory_state(const std::string& key) {
    return m_key_to_state.emplace(key, create_memory_state(key)).first->second;
}

MemoryState MemoryStateFactory::get_memory_state(const std::string& key) const {
    auto find = m_key_to_state.find(key);
    if (find == m_key_to_state.end()) {
        throw std::runtime_error("MemoryStateFactory::get_memory_state - no memory state exists for key: " + key);
    }
    return find->second;
}

}
