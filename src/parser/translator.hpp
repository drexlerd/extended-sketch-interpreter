#ifndef SRC_PARSER_TRANSLATOR_HPP_
#define SRC_PARSER_TRANSLATOR_HPP_

#include <tuple>
#include <variant>

#include "../extended_sketch/declarations.hpp"

#include "ast.hpp"
#include "context.hpp"
#include "config.hpp"


namespace sketches::extended_sketch::parser {

/// @brief Stage 1 translation of AST into extended sketches language.
extern ExtendedSketch translate(Context& context, const error_handler_type& error_handler, const ast::ExtendedSketch& node);

}

#endif

