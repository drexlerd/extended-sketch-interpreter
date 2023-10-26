#ifndef SRC_EXTENDED_SKETCH_SIGNATURE_HPP_
#define SRC_EXTENDED_SKETCH_SIGNATURE_HPP_

#include <string>

#include "arguments.hpp"

namespace sketches::extended_sketch {

class Signature {
private:
    std::string name;
    ArgumentList arguments;

public:
    Signature(const std::string& name, const ArgumentList& arguments);

    const std::string& get_name() const;
    const ArgumentList& get_arguments() const;

    std::string get_signature() const;
};

}

#endif