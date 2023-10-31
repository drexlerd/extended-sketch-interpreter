#include "signature.hpp"

#include <sstream>


namespace sketches::extended_sketch {

Signature::Signature(const std::string& name, const ArgumentList& arguments)
    : name(name), arguments(arguments) { }

const std::string& Signature::get_name() const {
    return name;
}

const ArgumentList& Signature::get_arguments() const {
    return arguments;
}

std::string Signature::compute_signature() const {
    std::stringstream ss;
    ss << name
       << "(";
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i != 0) ss << ",";
        std::visit([&](auto&& arg){ ss << arg.get_type_name() << " " << arg.get_value_name(); }, arguments[i]);
    }
    ss << ")";
    return ss.str();
}
}