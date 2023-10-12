#ifndef SRC_PARSER_AST_HPP_
#define SRC_PARSER_AST_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <map>
#include <vector>

namespace sketches::extended_sketch { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    struct Name;
    struct QuotedString;
    struct MemoryState;
    struct MemoryStates;
    struct Register;
    struct Registers;
    struct Boolean;
    struct Booleans;
    struct LoadRule;
    struct CallRule;
    struct ActionRule;
    struct SearchRule;
    struct Rule;
    struct Rules;
    struct ExtendedSketch;


    struct Name : x3::position_tagged {
        std::string name;
    };

    struct QuotedString : x3::position_tagged {
        std::string name;
    };

    struct MemoryState : x3::position_tagged {
        Name key;
    };

    struct MemoryStates : x3::position_tagged {
        std::vector<MemoryState> states;
    };

    struct Register : x3::position_tagged {
        Name key;
    };

    struct Registers : x3::position_tagged {
        std::vector<Register> registers;
    };

    struct Boolean : x3::position_tagged {
        Name key;
        QuotedString repr;
    };

    struct Booleans : x3::position_tagged {
        std::vector<Boolean> booleans;
    };

    struct LoadRule : x3::position_tagged {

    };

    struct CallRule : x3::position_tagged {

    };

    struct ActionRule : x3::position_tagged {

    };

    struct SearchRule : x3::position_tagged {

    };

    struct Rule : x3::position_tagged, x3::variant<LoadRule, CallRule, ActionRule, SearchRule> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Rules {
        std::vector<Rule> rules;
    };

    struct ExtendedSketch : x3::position_tagged {
        Name name;
        Rules rules;
    };

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