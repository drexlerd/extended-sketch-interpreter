#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_ADAPTED_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_ADAPTED_HPP_

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "ast.hpp"


// We need to tell fusion about our rexpr and rexpr_key_value
// to make them a first-class fusion citizens
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Name, alphabetical, suffix)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ArgumentRegister, type_name, value_name)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ArgumentConcept, type_name, value_name)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Signature, name, arguments)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryState, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryStateReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryStates, definitions)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::InitialMemoryState, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Register, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::RegisterReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Registers, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryCondition, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryEffect, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::LoadRule, memory_condition, feature_conditions, memory_effect, feature_effects, register_reference, concept_reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketchReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::CallRule, memory_condition, feature_conditions, memory_effect, feature_effects, extended_sketch_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ActionReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ActionRule, memory_condition, feature_conditions, memory_effect, feature_effects, action_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::SearchRule, memory_condition, feature_conditions, memory_effect, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Rules, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch, signature, memory_states, initial_memory_state, registers, booleans, numericals, concepts, rules)

#endif
