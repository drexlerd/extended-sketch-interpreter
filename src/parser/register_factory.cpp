#include "register_factory.hpp"

#include "register.hpp"


namespace sketches::extended_sketch {

Register RegisterFactory::make_register(const std::string& key) {
    return m_key_to_state.emplace(key, make_register(key)).first->second;
}

Register RegisterFactory::get_register(const std::string& key) const {
    auto find = m_key_to_state.find(key);
    if (find == m_key_to_state.end()) {
        throw std::runtime_error("RegisterFactory::get_register - no register exists for key: " + key);
    }
    return find->second;
}

}
