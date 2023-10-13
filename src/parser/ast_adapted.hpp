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
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::InitialMemoryStateEntry, reference)

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

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::PositiveBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::NegativeBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::UnchangedBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::IncrementNumericalEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::DecrementNumericalEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::UnchangedNumericalEffectEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::LoadRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, register_reference, concept_reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ModuleReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::CallRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, module_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ActionRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, action_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::SearchRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::Rules, rules)
// BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketch, name, memory_states, initial_memory_state, registers, booleans, numericals, concepts, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::extended_sketch::ast::ExtendedSketch, name, memory_states, initial_memory_state, registers)

#endif
