#ifndef SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_

#include <string>

#include "arguments.hpp"

namespace mimir::extended_sketch {

class ModuleCall {
private:
    std::string name;
    ArgumentList arguments;

public:
    ModuleCall(const std::string& name, const ArgumentList& arguments);

    const std::string& get_name() const;
    const ArgumentList& get_arguments() const;

    std::string compute_signature() const;
};

}

#endif