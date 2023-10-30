#ifndef SRC_PARSERS_MODULE_STAGE_1_AST_HPP_
#define SRC_PARSERS_MODULE_STAGE_1_AST_HPP_

#include <string>
#include <vector>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include "src/parsers/extended_sketch/stage_1/ast.hpp"


namespace sketches::parsers::module::stage_1::ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    /* Signature entry */
    struct Signature : x3::position_tagged {
        Name name;
        std::vector<Argument> arguments;
    };

    struct Module : x3::position_tagged {
        Signature signature;
        extended_sketch::stage_1::ast::ExtendedSketch extended_sketches;
    };
}


#endif