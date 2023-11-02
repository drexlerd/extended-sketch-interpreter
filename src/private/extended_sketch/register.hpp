#ifndef SRC_PRIVATE_EXTENDED_SKETCH_REGISTER_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_REGISTER_HPP_

#include <string>

#include "declarations.hpp"


namespace mimir::extended_sketch {
struct RegisterImpl {
    std::string name;

    RegisterImpl(const std::string& name);

    std::string compute_signature() const;
};

extern Register make_register(const std::string& name);

}

#endif
