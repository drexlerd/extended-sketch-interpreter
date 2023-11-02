#ifndef SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_
#define SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_

#include <string>
#include <variant>
#include <vector>

#include "declarations.hpp"


namespace mimir::extended_sketch {
class ArgumentRegister;
class ArgumentConcept;
using Argument = std::variant<ArgumentRegister, ArgumentConcept>;
using ArgumentList = std::vector<Argument>;



class ArgumentRegister {
private:
    Register m_register;

public:
    ArgumentRegister();
    ArgumentRegister(const Register& register_);

    std::string compute_signature() const;
};


class ArgumentConcept {
private:
    Concept m_concept;

public:
    ArgumentConcept();
    ArgumentConcept(const Concept& concept_);

    std::string compute_signature() const;
};


}

#endif