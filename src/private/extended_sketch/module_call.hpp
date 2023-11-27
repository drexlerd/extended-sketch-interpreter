#ifndef SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_
#define SRC_PRIVATE_EXTENDED_SKETCH_MODULE_CALL_HPP_

#include <string>

#include "declarations.hpp"


namespace mimir::extended_sketch {

class ModuleCall {
private:
    std::string m_name;
    // For simplicity, we group parameters by their type.
    ConceptList m_concept_arguments;
    RoleList m_role_arguments;

public:
    ModuleCall(const std::string& name, const ConceptList& concept_arguments, const RoleList& role_arguments);

    const std::string& get_name() const;
    const ConceptList& get_concept_arguments() const;
    const RoleList& get_role_arguments() const;

    std::string compute_signature() const;
};

}

#endif