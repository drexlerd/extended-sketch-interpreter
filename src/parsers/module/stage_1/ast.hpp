#ifndef SRC_PARSERS_MODULE_STAGE_1_AST_HPP_
#define SRC_PARSERS_MODULE_STAGE_1_AST_HPP_

#include <string>
#include <vector>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_1/ast.hpp"


namespace sketches::parsers::module::stage_1::ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    struct Module : x3::position_tagged {

    };
}


#endif