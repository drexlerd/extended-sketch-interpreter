#include "arguments.hpp"


namespace sketches::extended_sketch {

BaseArgument::BaseArgument() : m_type_name(""), m_value_name("") { }

BaseArgument::BaseArgument(const std::string& type_name, const std::string& value_name)
    : m_type_name(type_name), m_value_name(value_name) { }

BaseArgument::~BaseArgument() = default;

const std::string& BaseArgument::get_type_name() const {
    return m_type_name;
}

const std::string& BaseArgument::get_value_name() const {
    return m_value_name;
}


ArgumentRegister::ArgumentRegister(const std::string& type_name, const std::string& value_name)
    : BaseArgument(type_name, value_name) { }

ArgumentConcept::ArgumentConcept(const std::string& type_name, const std::string& value_name)
    : BaseArgument(type_name, value_name) { }

}