#include "parameters.hpp"


namespace sketches::extended_sketch {


ParameterRegister::ParameterRegister()
    : m_name("") { }

ParameterRegister::ParameterRegister(const std::string& name_)
    : m_name(name_) { }

std::string ParameterRegister::compute_signature() const {
    return ":register " + m_name;
}



ParameterConcept::ParameterConcept()
    : m_name("") { }

ParameterConcept::ParameterConcept(const std::string& name_)
    : m_name(name_) { }

std::string ParameterConcept::compute_signature() const {
    return ":concept " + m_name;
}


}