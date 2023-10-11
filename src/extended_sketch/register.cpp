#include "register.hpp"


namespace sketches::extended_sketch {

RegisterImpl::RegisterImpl(const std::string& key)
    : m_key(key) { }

const std::string& RegisterImpl::get_key() const {
    return m_key;
}

std::shared_ptr<RegisterImpl> create_register(const std::string& key) {
    return std::make_shared<RegisterImpl>(key);
}

}