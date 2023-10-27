#include "call.hpp"

#include <sstream>


namespace sketches::extended_sketch {

Call::Call(const std::string& name, const ArgumentList& arguments)
    : name(name), arguments(arguments) { }

const std::string& Call::get_name() const {
    return name;
}

const ArgumentList& Call::get_arguments() const {
    return arguments;
}

std::string Call::compute_signature() const {
    std::stringstream ss;
    ss << name
       << "(";
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i != 0) {
            ss << ",";
        }
        std::visit([&](auto&& arg){ ss << arg.get_type_name(); }, arguments[i]);
    }
    ss << ")";
    return ss.str();
}
}