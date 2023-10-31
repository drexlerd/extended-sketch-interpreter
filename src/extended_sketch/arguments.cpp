#include "arguments.hpp"

#include "register.hpp"


namespace sketches::extended_sketch {


ArgumentRegister::ArgumentRegister()
    : m_register(nullptr) { }

ArgumentRegister::ArgumentRegister(const Register& register_)
    : m_register(register_) { }

std::string ArgumentRegister::compute_signature() const {
    return ":register " + m_register->compute_signature();
}

ArgumentConcept::ArgumentConcept()
    : m_concept(nullptr) { }

ArgumentConcept::ArgumentConcept(const Concept& concept_)
    : m_concept(concept_) { }

std::string ArgumentConcept::compute_signature() const {
    return ":register " + m_concept->get_key();
}

}