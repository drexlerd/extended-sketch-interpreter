#include "parser.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "src/parsers/common/config.hpp"
#include "src/parsers/extended_sketch/common/error_handler.hpp"

#include "ast.hpp"
#include "parser_api.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser {
ParseAstResult parse_ast(const std::string& sketch_file_content) {
    using sketches::parsers::iterator_type;
    iterator_type iter(sketch_file_content.begin());
    iterator_type const end(sketch_file_content.end());
    return parse_ast(sketch_file_content, iter, end);
}

extern ParseAstResult parse_ast(const std::string& sketch_file_content, iterator_type iter, iterator_type end) {
    // Our AST
    sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch ast;

    // Our error handler
    using boost::spirit::x3::with;
    using sketches::parsers::error_handler_type;
    using sketches::parsers::error_handler_tag;
    //std::stringstream out;
    error_handler_type error_handler(iter, end, std::cerr); // Our error handler

    // Our parser
    auto const parser =
        // we pass our error handler to the parser so we can access
        // it later on in our on_error and on_sucess handlers
        with<error_handler_tag>(std::ref(error_handler))
        [
            sketches::parsers::extended_sketch::stage_1::extended_sketch()
        ];

    // Go forth and parse!
    using boost::spirit::x3::ascii::space;
    bool success = phrase_parse(iter, end, parser, space, ast) && iter == end;
    if (!success)
    {
        //std::cerr << out.str() << std::endl;
        throw std::runtime_error("Unsuccessful parse.");
    }

    return {ast, error_handler};
}

}

