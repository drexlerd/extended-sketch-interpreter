#ifndef SRC_PRIVATE_EXTENDED_SKETCH_SIGNATURE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_SIGNATURE_HPP_

#include <string>

#include "../extended_sketch/parameters.hpp"

namespace mimir::extended_sketch {

class Signature {
private:
    std::string m_name;
    ParameterList m_parameters;

public:
    Signature(const std::string& name, const ParameterList& arguments);

    const std::string& get_name() const;
    const ParameterList& get_parameters() const;

    std::string compute_signature() const;
};

}

#endif