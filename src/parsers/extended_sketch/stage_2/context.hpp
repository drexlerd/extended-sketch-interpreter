#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_CONTEXT_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_CONTEXT_HPP_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_2/context.hpp"

#include "src/extended_sketch/declarations.hpp"
#include "src/parsers/extended_sketch/stage_1/ast.hpp"


namespace sketches::parsers::extended_sketch::stage_2 {
    /// @brief Provides additional context during parsing.
    struct Context {
        // Mimir context
        mimir::formalism::DomainDescription domain_description;
        std::map<std::string, mimir::formalism::ActionSchema> action_schema_map;

        // Dlplan context
        dlplan::policy::parsers::policy::stage_2::parser::Context dlplan_context;

        // Our context
        std::unordered_map<std::string, sketches::extended_sketch::Register> registers;
        std::unordered_map<std::string, sketches::extended_sketch::MemoryState> memory_states;

        /// @brief Constructor for parsing an extended sketch
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

        /// @brief Constructor for parsing module
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory,
            dlplan::policy::parsers::policy::stage_2::parser::Context& dlplan_context,
            std::unordered_map<std::string, sketches::extended_sketch::Register>& registers,
            std::unordered_map<std::string, sketches::extended_sketch::MemoryState>& memory_states);
    };
}

#endif