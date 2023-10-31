#ifndef SRC_EXTENDED_SKETCH_PARAMETERS_HPP_
#define SRC_EXTENDED_SKETCH_PARAMETERS_HPP_

#include <string>
#include <variant>
#include <vector>

#include "declarations.hpp"


namespace sketches::extended_sketch {
class ParameterRegister;
class ParameterConcept;
using Parameter = std::variant<ParameterRegister, ParameterConcept>;
using ParameterList = std::vector<Parameter>;


class ParameterRegister {
private:
    std::string m_name;

public:
    ParameterRegister();
    ParameterRegister(const std::string& name_);

    std::string compute_signature() const;
};


class ParameterConcept {
private:
    std::string m_name;

public:
    ParameterConcept();
    ParameterConcept(const std::string& name_);

    std::string compute_signature() const;
};


}

#endif