#include "module.hpp"

#include "signature.hpp"
#include "extended_sketch.hpp"


namespace sketches::extended_sketch {

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

Module make_module(
    const Signature& signature,
    const ExtendedSketch& extended_sketch) {
    return std::make_shared<ModuleImpl>(signature, extended_sketch);
}


}