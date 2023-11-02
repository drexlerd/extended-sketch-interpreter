#include "parameters.hpp"

#include "register.hpp"


namespace mimir::extended_sketch {


ParameterRegister::ParameterRegister()
    : m_register(nullptr) { }

ParameterRegister::ParameterRegister(const Register& register_)
    : m_register(register_) { }

std::string ParameterRegister::compute_signature() const {
    return ":register " + m_register->compute_signature();
}



ParameterConcept::ParameterConcept()
    : m_concept(nullptr) { }

ParameterConcept::ParameterConcept(const Concept& concept_)
    : m_concept(concept_) {
    // Initially, the underlying feature is a nullptr.
    assert(m_concept->get_concept() == nullptr);
}

std::string ParameterConcept::compute_signature() const {
    return ":concept " + m_concept->str();
}


}