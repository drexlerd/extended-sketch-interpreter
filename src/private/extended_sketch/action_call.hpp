#ifndef SRC_PRIVATE_EXTENDED_SKETCH_ACTION_CALL_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_ACTION_CALL_HPP_

#include "arguments.hpp"

#include "../formalism/action_schema.hpp"

#include <string>


namespace mimir::extended_sketch {

class ActionCall {
private:
    mimir::formalism::ActionSchema action_schema;
    ArgumentList arguments;

public:
    ActionCall(const mimir::formalism::ActionSchema& action_schema, const ArgumentList& arguments);

    const mimir::formalism::ActionSchema& get_action_schema() const;
    const ArgumentList& get_arguments() const;

    std::string compute_signature() const;
};

}

#endif