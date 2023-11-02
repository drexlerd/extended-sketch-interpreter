#ifndef SRC_EXTENDED_SKETCH_PARAMETERS_HPP_
#define SRC_EXTENDED_SKETCH_PARAMETERS_HPP_

#include <string>
#include <variant>
#include <vector>

#include "declarations.hpp"


namespace mimir::extended_sketch {
class ParameterRegister;
class ParameterConcept;
using Parameter = std::variant<ParameterRegister, ParameterConcept>;
using ParameterList = std::vector<Parameter>;


class ParameterRegister {
private:
    Register m_register;

public:
    ParameterRegister();
    ParameterRegister(const Register& register_);

    std::string compute_signature() const;
};


class ParameterConcept {
private:
    // Hack: We modify the named concept by removing its const.
    // This is not an issue from the perspective of caching concepts in the factory
    // because they are cached with by the key and not by the representation of the feature.
    Concept m_concept;

public:
    ParameterConcept();
    ParameterConcept(const Concept& concept_);

    std::string compute_signature() const;
};


}

#endif