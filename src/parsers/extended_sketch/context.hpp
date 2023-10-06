#ifndef SRC_PARSERS_EXTENDED_SKETCH_CONTEXT_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_CONTEXT_HPP_

#include <memory>

#include "../../external/dlplan/include/dlplan/core.h"
#include "../../external/dlplan/include/dlplan/policy.h"


namespace sketches::extended_sketch::parser {
    /// @brief Provides additional context during parsing.
    struct Context {
        std::shared_ptr<dlplan::core::SyntacticElementFactory> dlplan_element_factory;
        std::shared_ptr<dlplan::policy::PolicyBuilder> policy_builder;
    };
}

#endif