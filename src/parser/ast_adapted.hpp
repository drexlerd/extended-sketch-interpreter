#ifndef SRC_PARSER_AST_ADAPTED_HPP_
#define SRC_PARSER_AST_ADAPTED_HPP_


#include "ast.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

// We need to tell fusion about our rexpr and rexpr_key_value
// to make them a first-class fusion citizens
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Name, alphabetical, suffix)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::QuotedString, characters)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NameEntry, name)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStateDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStateReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryStatesEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::RegisterDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::RegisterReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::RegistersEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::BooleanDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::BooleanReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::BooleansEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NumericalDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NumericalReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NumericalsEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ConceptDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ConceptReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ConceptsEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::MemoryEffectEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::PositiveBooleanConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NegativeBooleanConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::GreaterNumericalConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::EqualNumericalConditionEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::PositiveBooleanEffect, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NegativeBooleanEffect, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::UnchangedBooleanEffect, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::IncrementNumericalEffect, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::DecrementNumericalEffect, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::UnchangedNumericalEffect, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::FeatureConditionsEntry, feature_conditions)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::FeatureEffectsEntry, feature_effects)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::LoadRule, memory_condition, feature_conditions, memory_effect, register_reference, concept_reference, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::CallRule, memory_condition, feature_conditions, memory_effect, module_reference, register_references, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionRule, memory_condition, feature_conditions, memory_effect, action_reference, register_references, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::SearchRule, memory_condition, feature_conditions, memory_effect, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Rules, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketch, name, memory_states, registers, booleans, numericals, concepts, rules)


#endif
