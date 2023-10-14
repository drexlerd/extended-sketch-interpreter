#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_PARSER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_PARSER_HPP_

#include <tuple>
#include <variant>

#include "src/extended_sketch/declarations.hpp"
#include "src/parsers/common/config.hpp"
#include "src/parsers/extended_sketch/stage_1_ast/ast.hpp"

#include "context.hpp"


namespace sketches::parsers::extended_sketch::stage_2 {

/// @brief Stage 1 translation of AST into extended sketches language.
extern ExtendedSketch parse_sketch(Context& context, const error_handler_type& error_handler, const stage_1::ast::ExtendedSketch& node);

}

#endif

