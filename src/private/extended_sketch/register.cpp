#include "register.hpp"


namespace mimir::extended_sketch {

RegisterImpl::RegisterImpl(const std::string& name)
    : name(name) {
}

std::string RegisterImpl::compute_signature() const {
    return name;
}

Register make_register(const std::string& name) {
    return std::make_shared<RegisterImpl>(name);
}

}