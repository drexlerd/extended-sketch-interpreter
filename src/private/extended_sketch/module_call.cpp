#include "module_call.hpp"

#include <sstream>


namespace mimir::extended_sketch {

ModuleCall::ModuleCall(const std::string& name, const ConceptList& concept_arguments, const RoleList& role_arguments)
    : m_name(name), m_concept_arguments(concept_arguments), m_role_arguments(role_arguments) { }

const std::string& ModuleCall::get_name() const {
    return m_name;
}

const ConceptList& ModuleCall::get_concept_arguments() const {
    return m_concept_arguments;
}

const RoleList& ModuleCall::get_role_arguments() const {
    return m_role_arguments;
}

std::string ModuleCall::compute_signature() const {
    std::stringstream ss;
    ss << m_name
       << "(";
    for (size_t i = 0; i < m_concept_arguments.size(); ++i) {
        if (i != 0) ss << ",";
        ss << m_concept_arguments[i]->str();
    }

    // add separator between concepts and roles
    if (!m_concept_arguments.empty() && !m_role_arguments.empty()) ss << ",";

    for (size_t i = 0; i < m_role_arguments.size(); ++i) {
        if (i != 0) ss << ",";
        ss << m_role_arguments[i]->str();
    }
    ss << ")";
    return ss.str();
}
}