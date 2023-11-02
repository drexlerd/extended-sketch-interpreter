#ifndef SRC_EXTENDED_SKETCH_CALL_HPP_
#define SRC_EXTENDED_SKETCH_CALL_HPP_

#include <string>

#include "arguments.hpp"

namespace mimir::extended_sketch {

class Call {
private:
    std::string name;
    ArgumentList arguments;

public:
    Call(const std::string& name, const ArgumentList& arguments);

    const std::string& get_name() const;
    const ArgumentList& get_arguments() const;

    std::string compute_signature() const;
};

}

#endif