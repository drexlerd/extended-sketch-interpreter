#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_ADAPTED_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_ADAPTED_HPP_

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "ast.hpp"


// We need to tell fusion about our rexpr and rexpr_key_value
// to make them a first-class fusion citizens
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Name, alphabetical, suffix)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::QuotedString, characters)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NameEntry, name)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryStateDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryStateReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryStatesEntry, definitions)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::InitialMemoryStateEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::RegisterDefinition, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::RegisterReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::RegistersEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::BooleanDefinition, key, repr)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::BooleanReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::BooleansEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NumericalDefinition, key, repr)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NumericalReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NumericalsEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ConceptDefinition, key, repr)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ConceptReference, key)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ConceptsEntry, definitions)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::MemoryEffectEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::PositiveBooleanConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NegativeBooleanConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::GreaterNumericalConditionEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::EqualNumericalConditionEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::PositiveBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::NegativeBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::UnchangedBooleanEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::IncrementNumericalEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::DecrementNumericalEffectEntry, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::UnchangedNumericalEffectEntry, reference)

BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::LoadRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, register_reference, concept_reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ModuleReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::CallRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, module_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ActionReference, reference)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ActionRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects, action_reference, register_references)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::SearchRuleEntry, memory_condition, feature_conditions, memory_effect, feature_effects)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::Rules, rules)
BOOST_FUSION_ADAPT_STRUCT(sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch, name, memory_states, initial_memory_state, registers, booleans, numericals, concepts, rules)

#endif
