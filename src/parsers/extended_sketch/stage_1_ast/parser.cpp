#include "parser.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "src/parsers/common/config.hpp"
#include "src/parsers/common/error_handler.hpp"
#include "src/parsers/extended_sketch/common/error_handler.hpp"

#include "ast.hpp"
#include "parser_api.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser {

ast::ExtendedSketch parse_ast(
    iterator_type& iter,
    iterator_type end,
    error_handler_type& error_handler) {
    assert(in_bounds(iter, end, error_handler));

    // Our AST
    sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch ast;

    // Our parser
    using boost::spirit::x3::with;
    using sketches::parsers::error_handler_tag;
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
        throw std::runtime_error("Unsuccessful parse.");
    }

    return ast;
}

}

