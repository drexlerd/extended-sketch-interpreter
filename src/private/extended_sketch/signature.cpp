#include "signature.hpp"

#include <sstream>


namespace mimir::extended_sketch {

Signature::Signature(const std::string& name, const ParameterList& parameters)
    : m_name(name), m_parameters(parameters) { }

const std::string& Signature::get_name() const {
    return m_name;
}

const ParameterList& Signature::get_parameters() const {
    return m_parameters;
}

std::string Signature::compute_signature() const {
    std::stringstream ss;
    ss << m_name
       << "(";
    for (size_t i = 0; i < m_parameters.size(); ++i) {
        if (i != 0) ss << ",";
        std::visit([&](auto&& arg){ ss << arg.compute_signature(); }, m_parameters[i]);
    }
    ss << ")";
    return ss.str();
}
}