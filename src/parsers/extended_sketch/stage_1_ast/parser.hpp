#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_

#include "ast.hpp"

#include "src/parsers/common/config.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser {


/// @brief Parses the content from iter to end
extern ast::ExtendedSketch parse_ast(
     iterator_type& iter,
     iterator_type end,
     error_handler_type& error_handler);

}

#endif
