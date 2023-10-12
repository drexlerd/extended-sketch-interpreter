#ifndef SRC_PARSER_AST_ADAPTED_HPP_
#define SRC_PARSER_AST_ADAPTED_HPP_


#include "ast.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

// We need to tell fusion about our rexpr and rexpr_key_value
// to make them a first-class fusion citizens
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Name, name)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::QuotedString, name)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryState, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStates, states)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Register, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Registers, registers)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Boolean, key, repr)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Booleans, booleans)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::LoadRule)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::CallRule)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionRule)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::SearchRule)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Rules, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketch, name, rules)


#endif
