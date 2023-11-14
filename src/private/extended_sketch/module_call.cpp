#include "module_call.hpp"

#include <sstream>


namespace mimir::extended_sketch {

ModuleCall::ModuleCall(const std::string& name, const ConceptList& arguments)
    : name(name), arguments(arguments) { }

const std::string& ModuleCall::get_name() const {
    return name;
}

const ConceptList& ModuleCall::get_arguments() const {
    return arguments;
}

std::string ModuleCall::compute_signature() const {
    std::stringstream ss;
    ss << name
       << "(";
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i != 0) {
            ss << ",";
        }
        ss << arguments[i]->str();
    }
    ss << ")";
    return ss.str();
}
}