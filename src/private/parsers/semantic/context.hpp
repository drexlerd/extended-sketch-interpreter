#ifndef SRC_PRIVATE_PARSERS_SEMANTIC_CONTEXT_HPP_
#define SRC_PRIVATE_PARSERS_SEMANTIC_CONTEXT_HPP_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "../../formalism/domain.hpp"
#include "../../dlplan/include/dlplan/core.h"
#include "../../dlplan/include/dlplan/policy.h"
#include "../../dlplan/include/dlplan/policy/parsers/semantic/context.hpp"

#include "../../extended_sketch/declarations.hpp"
#include "../../parsers/syntactic/ast.hpp"


namespace mimir::extended_sketch {
    template<typename Node, typename Result>
    struct Data {
        Node node;
        Result result;
    };


    /// @brief Provides additional context during parsing.
    struct Context {
        // Mimir context
        mimir::formalism::DomainDescription domain_description;
        std::map<std::string, mimir::formalism::ActionSchema> action_schema_map;

        // Dlplan context
        dlplan::policy::Context dlplan_context;

        // Our context
        std::unordered_map<std::string, Data<ast::MemoryState, MemoryState>> memory_states;

        // We realise arguments as registers and refer to them via concepts
        std::unordered_map<Concept, int> register_mapping;

        /// @brief Constructor for parsing an extended sketch
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

        /// @brief Constructor for parsing module
        Context(
            const mimir::formalism::DomainDescription& domain_description,
            const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory,
            dlplan::policy::Context& dlplan_context,
            std::unordered_map<std::string, Register>& registers,
            std::unordered_map<std::string, MemoryState>& memory_states);
    };
}

#endif