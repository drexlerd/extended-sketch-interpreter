#include "arguments.hpp"


namespace sketches::extended_sketch {

Argument::Argument(const std::string& key) : m_key(key) { }

Argument::~Argument() = default;

const std::string& Argument::get_key() const {
    return m_key;
}

ArgumentRegister::ArgumentRegister(const std::string& key)
    : Argument(key) { }

ArgumentConcept::ArgumentConcept(const std::string& key)
    : Argument(key) { }

}