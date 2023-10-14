#ifndef SRC_PARSER_STAGE_2_AST_TRANSLATOR_HPP_
#define SRC_PARSER_STAGE_2_AST_TRANSLATOR_HPP_

#include <tuple>
#include <variant>

#include "src/extended_sketch/declarations.hpp"
#include "src/parser/common/config.hpp"
#include "src/parser/stage_1_ast/ast.hpp"

#include "context.hpp"


namespace sketches::extended_sketch::parser {

/// @brief Stage 1 translation of AST into extended sketches language.
extern ExtendedSketch parse_sketch(Context& context, const error_handler_type& error_handler, const ast::ExtendedSketch& node);

}

#endif

