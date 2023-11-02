#ifndef SRC_PRIVATE_PARSERS_SEMANTIC_PARSER_HPP_
#define SRC_PRIVATE_PARSERS_SEMANTIC_PARSER_HPP_

#include <tuple>
#include <variant>

#include "src/private/dlplan/include/dlplan/common/parsers/config.hpp"
#include "src/private/extended_sketch/declarations.hpp"
#include "src/private/parsers/syntactic/ast.hpp"


#include "context.hpp"


namespace mimir::extended_sketch {
extern ExtendedSketch parse(
    const ast::ExtendedSketch& node,
    const dlplan::error_handler_type& error_handler,
    Context& context);

extern Module parse(
    const ast::Module& node,
    const dlplan::error_handler_type& error_handler,
    Context& context);

}

#endif

