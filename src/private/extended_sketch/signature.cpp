#include "signature.hpp"

#include <sstream>


namespace mimir::extended_sketch {

Signature::Signature(const std::string& name, const ConceptList& parameters)
    : m_name(name), m_parameters(parameters) { }

const std::string& Signature::get_name() const {
    return m_name;
}

const ConceptList& Signature::get_parameters() const {
    return m_parameters;
}

std::string Signature::compute_signature() const {
    std::stringstream ss;
    ss << m_name
       << "(";
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        if (i != 0) ss << ",";
        ss << m_parameters[i]->str();
    }
    ss << ")";
    return ss.str();
}
}