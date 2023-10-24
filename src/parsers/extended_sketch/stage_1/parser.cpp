#include "parser.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>


#include "ast.hpp"
#include "parser_api.hpp"

using namespace dlplan::common::parsers;


namespace sketches::parsers::extended_sketch::stage_1::parser {

ast::ExtendedSketch parse(
    iterator_type& iter,
    iterator_type end,
    error_handler_type& error_handler) {

    // Our AST
    sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch ast;

    // Our parser
    using boost::spirit::x3::with;
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

