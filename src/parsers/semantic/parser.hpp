#ifndef SRC_PARSERS_SEMANTIC_PARSER_HPP_
#define SRC_PARSERS_SEMANTIC_PARSER_HPP_

#include <tuple>
#include <variant>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/parsers/syntactic/ast.hpp"


#include "context.hpp"


namespace sketches::extended_sketch {
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

