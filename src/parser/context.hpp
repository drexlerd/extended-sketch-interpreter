#ifndef SRC_PARSER_CONTEXT_HPP_
#define SRC_PARSER_CONTEXT_HPP_

#include <map>
#include <memory>
#include <string>

#include "../external/mimir/formalism/domain.hpp"
#include "../external/dlplan/include/dlplan/core.h"
#include "../external/dlplan/include/dlplan/policy.h"

#include "feature_factory.hpp"
#include "memory_state_factory.hpp"
#include "register_factory.hpp"


namespace sketches::extended_sketch::parser {
    /// @brief Provides additional context during parsing.
    struct Context {
        mimir::formalism::DomainDescription domain_description;
        std::map<std::string, mimir::formalism::ActionSchema> action_schema_map;

        std::shared_ptr<dlplan::policy::PolicyBuilder> policy_builder;
        MemoryStateFactory memory_state_factory;
        RegisterFactory register_factory;
        BooleanFactory boolean_factory;
        NumericalFactory numerical_factory;
        ConceptFactory concept_factory;

        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::core::SyntacticElementFactory>& syntactic_element_factory,
            const std::shared_ptr<dlplan::policy::PolicyBuilder>& policy_builder);
    };
}

#endif