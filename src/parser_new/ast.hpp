#ifndef SRC_PARSER_AST_HPP_
#define SRC_PARSER_AST_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <map>

namespace sketches::extended_sketch { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    struct rexpr;

    struct rexpr_value : x3::variant<
            std::string
          , x3::forward_ast<rexpr>
        >
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    typedef std::map<std::string, rexpr_value> rexpr_map;
    typedef std::pair<std::string, rexpr_value> rexpr_key_value;

    struct rexpr : x3::position_tagged
    {
        rexpr_map entries;
    };
}}


#endif