#include "extended_sketch_parser.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "ast.hpp"
#include "rexpr.hpp"
#include "error_handler.hpp"
#include "config.hpp"
#include "printer.hpp"


namespace sketches::extended_sketch::parser {
ExtendedSketchParser::ExtendedSketchParser(const fs::path& sketch_path)
    : m_sketch_path(sketch_path) { }

ExtendedSketch ExtendedSketchParser::parse(
    const mimir::formalism::DomainDescription& domain_description,
    std::shared_ptr<dlplan::core::SyntacticElementFactory> factory,
    std::shared_ptr<dlplan::policy::PolicyBuilder> builder){

    std::ifstream sketch_stream(this->m_sketch_path.c_str());
    if (sketch_stream.is_open()) {
        std::stringstream buffer;
        buffer << sketch_stream.rdbuf();
        std::string source = buffer.str();

        using rexpr::parser::iterator_type;
        iterator_type iter(source.begin());
        iterator_type const end(source.end());

        // Our AST
        rexpr::ast::rexpr ast;

        // Our error handler
        using boost::spirit::x3::with;
        using rexpr::parser::error_handler_type;
        using rexpr::parser::error_handler_tag;
        std::stringstream out;
        error_handler_type error_handler(iter, end, out); // Our error handler

        // Our parser
        auto const parser =
            // we pass our error handler to the parser so we can access
            // it later on in our on_error and on_sucess handlers
            with<error_handler_tag>(std::ref(error_handler))
            [
                rexpr::rexpr()
            ];

        // Go forth and parse!
        using boost::spirit::x3::ascii::space;
        bool success = phrase_parse(iter, end, parser, space, ast) && iter != end;
        if (!success)
        {
            std::cerr << out.str() << std::endl;
        }

        return ExtendedSketch(nullptr);
    }
    throw std::runtime_error("extended sketch file does not exist");
}

}

