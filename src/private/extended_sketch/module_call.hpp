#ifndef SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_

#include <string>

#include "declarations.hpp"


namespace mimir::extended_sketch {

class ModuleCall {
private:
    std::string name;
    ConceptList arguments;

public:
    ModuleCall(const std::string& name, const ConceptList& arguments);

    const std::string& get_name() const;
    const ConceptList& get_arguments() const;

    std::string compute_signature() const;
};

}

#endif