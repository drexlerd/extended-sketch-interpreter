#include "action_call.hpp"

#include <sstream>


namespace mimir::extended_sketch {

ActionCall::ActionCall(const mimir::formalism::ActionSchema& action_schema, const ArgumentList& arguments)
    : action_schema(action_schema), arguments(arguments) { }

const mimir::formalism::ActionSchema& ActionCall::get_action_schema() const {
    return action_schema;
}

const ArgumentList& ActionCall::get_arguments() const {
    return arguments;
}

std::string ActionCall::compute_signature() const {
    std::stringstream ss;
    ss << action_schema->name
       << "(";
    for (size_t i = 0; i < arguments.size(); ++i) {
        if (i != 0) {
            ss << ",";
        }
        std::visit([&](auto&& arg){ ss << arg.compute_signature(); }, arguments[i]);
    }
    ss << ")";
    return ss.str();
}
}