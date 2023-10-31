#ifndef SRC_PARSERS_SYNTACTIC_AST_ADAPTED_HPP_
#define SRC_PARSERS_SYNTACTIC_AST_ADAPTED_HPP_

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "ast.hpp"


// We need to tell fusion about our rexpr and rexpr_key_value
// to make them a first-class fusion citizens
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Name, alphabetical, suffix)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ArgumentRegister, type_name, value_name)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ArgumentConcept, type_name, value_name)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryState, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStateReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStates, definitions)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::InitialMemoryState, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Register, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::RegisterReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Registers, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryCondition, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryEffect, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::LoadRule, memory_condition, feature_conditions, memory_effect, feature_effects, register_reference, concept_reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketchReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Call, name, arguments)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::CallRule, memory_condition, feature_conditions, memory_effect, feature_effects, call)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionRule, memory_condition, feature_conditions, memory_effect, feature_effects, action_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::SearchRule, memory_condition, feature_conditions, memory_effect, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Rules, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketch, memory_states, initial_memory_state, registers, booleans, numericals, concepts, rules)


BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Signature, name, arguments)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Module, signature, extended_sketch)


#endif