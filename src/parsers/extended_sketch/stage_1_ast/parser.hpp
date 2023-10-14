#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_

#include "ast.hpp"

#include "src/parsers/common/config.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser {

struct ParseAstResult {
     ast::ExtendedSketch root_node;
     error_handler_type error_handler;
};

/// @brief Parses the whole content
extern ParseAstResult parse_ast(const std::string& sketch_file_content);

/// @brief Parses the content from iter to end
extern ParseAstResult parse_ast(const std::string& sketch_file_content, iterator_type iter, iterator_type end);

}

#endif
