#ifndef SRC_PARSER_STAGE_1_AST_PARSER_HPP_
#define SRC_PARSER_STAGE_1_AST_PARSER_HPP_

#include "ast.hpp"

#include "src/parser/common/config.hpp"


namespace sketches::extended_sketch::parser {

struct ParseAstResult {
     ast::ExtendedSketch root_node;
     error_handler_type error_handler;
};

extern ParseAstResult parse_ast(const std::string& sketch_file_content);


}

#endif
