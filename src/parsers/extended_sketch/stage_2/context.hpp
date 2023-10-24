#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_CONTEXT_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_CONTEXT_HPP_

#include <map>
#include <memory>
#include <string>

#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_2/context.hpp"
#include "src/extended_sketch/extended_sketch_factory.hpp"

#include "feature_factory.hpp"
#include "memory_state_factory.hpp"
#include "register_factory.hpp"


namespace sketches::parsers::extended_sketch::stage_2 {
    /// @brief Provides additional context during parsing.
    struct Context {
        mimir::formalism::DomainDescription domain_description;
        std::map<std::string, mimir::formalism::ActionSchema> action_schema_map;

        std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory;
        std::shared_ptr<ExtendedSketchFactory> sketch_factory;

        MemoryStateFactory memory_state_factory;
        RegisterFactory register_factory;

        dlplan::policy::parsers::policy::stage_2::parser::Context dlplan_context;

        /// @brief Constructor for parsing an extended sketch
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

        /// @brief Constructor for parsing a module
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory,
            const std::shared_ptr<ExtendedSketchFactory>& sketch_factory);
    };
}

#endif