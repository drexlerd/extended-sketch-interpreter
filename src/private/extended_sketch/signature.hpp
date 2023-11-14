#ifndef SRC_PRIVATE_EXTENDED_SKETCH_SIGNATURE_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_SIGNATURE_HPP_

#include <string>
#include "declarations.hpp"


namespace mimir::extended_sketch {

class Signature {
private:
    std::string m_name;
    // Those are named concept expressions of form (name0, c_argument(0)), ..., (nameN, c_argument(N))
    ConceptList m_parameters;

public:
    Signature(const std::string& name, const ConceptList& parameters);

    const std::string& get_name() const;
    const ConceptList& get_parameters() const;

    std::string compute_signature() const;
};

}

#endif