#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_API_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_API_HPP_

#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"


namespace sketches::parsers::extended_sketch::stage_1
{
    namespace x3 = boost::spirit::x3;

    ///////////////////////////////////////////////////////////////////////////
    // rexpr public interface
    ///////////////////////////////////////////////////////////////////////////
    namespace parser {
        struct ExtendedSketchClass;
        typedef
            x3::rule<ExtendedSketchClass, ast::ExtendedSketch>
        extended_sketch_type;
        BOOST_SPIRIT_DECLARE(extended_sketch_type)
    }
    parser::extended_sketch_type const& extended_sketch();
}

#endif