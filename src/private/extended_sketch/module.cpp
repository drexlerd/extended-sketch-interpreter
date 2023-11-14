#include "module.hpp"

#include "signature.hpp"
#include "extended_sketch.hpp"

#include "../planners/atom_registry.hpp"


namespace mimir::extended_sketch {

ModuleImpl::ModuleImpl(
    const Signature& signature,
    const ExtendedSketch& extended_sketch)
    : signature(signature), extended_sketch(extended_sketch) { }

std::string ModuleImpl::compute_signature() const {
    std::stringstream ss;
    ss << "(:module\n"
       << "(:signature " << signature.compute_signature() << ")\n"
       << extended_sketch->compute_signature() << "\n"
       << ")";  // module
    return ss.str();
}

const Signature& ModuleImpl::get_signature() const {
    return signature;
}

const ExtendedSketch& ModuleImpl::get_extended_sketch() const {
    return extended_sketch;
}

Module make_module(
    const Signature& signature,
    const ExtendedSketch& extended_sketch) {
    return std::make_shared<ModuleImpl>(signature, extended_sketch);
}


}