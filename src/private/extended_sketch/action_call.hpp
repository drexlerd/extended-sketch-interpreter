#ifndef SRC_PRIVATE_EXTENDED_SKETCH_ACTION_CALL_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_ACTION_CALL_HPP_

#include "declarations.hpp"

#include "../formalism/action_schema.hpp"

#include <string>


namespace mimir::extended_sketch {

class ActionCall {
private:
    mimir::formalism::ActionSchema action_schema;
    ConceptList arguments;

public:
    ActionCall(const mimir::formalism::ActionSchema& action_schema, const ConceptList& arguments);

    const mimir::formalism::ActionSchema& get_action_schema() const;
    const ConceptList& get_arguments() const;

    std::string compute_signature() const;
};

}

#endif