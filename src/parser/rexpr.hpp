#ifndef SRC_PARSER_EMPLOYEE_HPP_
#define SRC_PARSER_EMPLOYEE_HPP_


#include "ast.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sketches::extended_sketch
{
    namespace x3 = boost::spirit::x3;

    ///////////////////////////////////////////////////////////////////////////
    // rexpr public interface
    ///////////////////////////////////////////////////////////////////////////
    namespace parser
    {
        struct rexpr_class;
        typedef
            x3::rule<rexpr_class, ast::rexpr>
        rexpr_type;
        BOOST_SPIRIT_DECLARE(rexpr_type)
    }
    namespace parser {
        struct ExtendedSketchClass;
        typedef
            x3::rule<ExtendedSketchClass, ast::ExtendedSketch>
        extended_sketch_type;
        BOOST_SPIRIT_DECLARE(extended_sketch_type)
    }

    parser::rexpr_type const& rexpr();
    parser::extended_sketch_type const& extended_sketch();
}

#endif