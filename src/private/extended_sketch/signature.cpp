#include "signature.hpp"

#include <sstream>


namespace mimir::extended_sketch {

Signature::Signature(const std::string& name, const ConceptList& concept_parameters, const RoleList& role_parameters)
    : m_name(name), m_concept_parameters(concept_parameters), m_role_parameters(role_parameters) { }

const std::string& Signature::get_name() const {
    return m_name;
}

const ConceptList& Signature::get_concept_parameters() const {
    return m_concept_parameters;
}

const RoleList& Signature::get_role_parameters() const {
    return m_role_parameters;
}

std::string Signature::compute_signature() const {
    std::stringstream ss;
    ss << m_name
       << "(";
    for (size_t i = 0; i < m_concept_parameters.size(); ++i) {
        if (i != 0) ss << ",";
        ss << m_concept_parameters[i]->str();
    }
    // add separator between concepts and roles
    if (!m_concept_parameters.empty() && !m_role_parameters.empty()) ss << ",";

    for (size_t i = 0; i < m_role_parameters.size(); ++i) {
        if (i != 0) ss << ",";
        ss << m_role_parameters[i]->str();
    }
    ss << ")";
    return ss.str();
}
}