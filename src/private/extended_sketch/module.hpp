#ifndef SRC_PRIVATE_MODULE_MODULE_HPP_
#define SRC_PRIVATE_MODULE_MODULE_HPP_

#include <string>
#include <unordered_map>

#include "declarations.hpp"
#include "signature.hpp"


namespace mimir::extended_sketch {

class ModuleImpl {
private:
    Signature signature;

    ExtendedSketch extended_sketch;

public:
    ModuleImpl(
        const Signature& signature,
        const ExtendedSketch& extended_sketch);

    std::string compute_signature() const;

    const ExtendedSketch& get_extended_sketch() const;
};

extern Module make_module(
    const Signature& signature,
    const ExtendedSketch& extended_sketch);

}

#endif