#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_PARSER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_PARSER_HPP_

#include <tuple>
#include <variant>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/parsers/extended_sketch/stage_1/ast.hpp"

#include "src/parsers/scope.hpp"

#include "context.hpp"


namespace sketches::parsers::extended_sketch::stage_2::parser {
// We add sketches to the global scope
// Their individual components are stored in their respective local scopes.
extern sketches::extended_sketch::ExtendedSketch parse(
    const stage_1::ast::ExtendedSketch& node,
    const dlplan::common::parsers::error_handler_type& error_handler,
    Context& context,
    Scope& global_scope);

}

#endif

