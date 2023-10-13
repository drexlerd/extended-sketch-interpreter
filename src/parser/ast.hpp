#ifndef SRC_PARSER_AST_HPP_
#define SRC_PARSER_AST_HPP_

#include <vector>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace sketches::extended_sketch { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    struct Name;
    struct QuotedString;
    struct NameEntry;
    struct MemoryStateDefinition;
    struct MemoryStateReference;
    struct MemoryStatesEntry;
    struct RegisterDefinition;
    struct RegisterReference;
    struct RegistersEntry;
    struct BooleanDefinition;
    struct BooleanReference;
    struct BooleansEntry;
    struct NumericalDefinition;
    struct NumericalReference;
    struct NumericalsEntry;
    struct ConceptDefinition;
    struct ConceptReference;
    struct ConceptsEntry;
    struct MemoryConditionEntry;
    struct MemoryEffectEntry;
    struct PositiveBooleanConditionEntry;
    struct NegativeBooleanConditionEntry;
    struct GreaterNumericalConditionEntry;
    struct EqualNumericalConditionEntry;
    struct PositiveBooleanEffectEntry;
    struct NegativeBooleanEffectEntry;
    struct UnchangedBooleanEffectEntry;
    struct IncrementNumericalEffectEntry;
    struct DecrementNumericalEffectEntry;
    struct UnchangedNumericalEffectEntry;
    struct FeatureConditionEntry;
    struct FeatureEffectEntry;
    struct LoadRuleEntry;
    struct CallRuleEntry;
    struct ActionRuleEntry;
    struct SearchRuleEntry;
    struct RuleEntry;
    struct Rules;
    struct ExtendedSketch;

    /* Basic character compounds */
    struct Name : x3::position_tagged {
        char alphabetical;
        std::string suffix;
    };

    struct QuotedString : x3::position_tagged {
        std::string characters;
    };


    /* Name entry */
    struct NameEntry : x3::position_tagged {
        Name name;
    };


    /* Memory state entry and references */
    struct MemoryStateDefinition : x3::position_tagged {
        Name key;
    };

    struct MemoryStateReference : x3::position_tagged {
        Name key;
    };

    struct MemoryStatesEntry : x3::position_tagged {
        std::vector<MemoryStateDefinition> definitions;
    };


    /* Register entry and references */
    struct RegisterDefinition : x3::position_tagged {
        Name key;
    };

    struct RegisterReference : x3::position_tagged {
        Name key;
    };

    struct RegistersEntry : x3::position_tagged {
        std::vector<RegisterDefinition> definitions;
    };


    /* Boolean entry and references */
    struct BooleanDefinition : x3::position_tagged {
        Name key;
        QuotedString repr;
    };

    struct BooleanReference : x3::position_tagged {
        Name key;
    };

    struct BooleansEntry : x3::position_tagged {
        std::vector<BooleanDefinition> definitions;
    };


    /* Numerical entry and references */
    struct NumericalDefinition : x3::position_tagged {
        Name key;
        QuotedString repr;
    };

    struct NumericalReference : x3::position_tagged {
        Name key;
    };

    struct NumericalsEntry : x3::position_tagged {
        std::vector<NumericalDefinition> definitions;
    };


    /* Concept entry and references */
    struct ConceptDefinition : x3::position_tagged {
        Name key;
        QuotedString repr;
    };

    struct ConceptReference : x3::position_tagged {
        Name key;
    };

    struct ConceptsEntry : x3::position_tagged {
        std::vector<ConceptDefinition> definitions;
    };


    /* Condition and effects */
    struct MemoryConditionEntry : x3::position_tagged {
        MemoryStateReference reference;
    };

    struct MemoryEffectEntry : x3::position_tagged {
        MemoryStateReference reference;
    };


    struct PositiveBooleanConditionEntry : x3::position_tagged {
        BooleanReference reference;
    };

    struct NegativeBooleanConditionEntry : x3::position_tagged {
        BooleanReference reference;
    };

    struct GreaterNumericalConditionEntry : x3::position_tagged {
        NumericalReference reference;
    };

    struct EqualNumericalConditionEntry : x3::position_tagged {
        NumericalReference reference;
    };

    struct FeatureConditionEntry : x3::position_tagged,
        x3::variant<
            x3::forward_ast<PositiveBooleanConditionEntry>,
            x3::forward_ast<NegativeBooleanConditionEntry>,
            x3::forward_ast<GreaterNumericalConditionEntry>,
            x3::forward_ast<EqualNumericalConditionEntry>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct PositiveBooleanEffectEntry : x3::position_tagged {
        BooleanReference reference;
    };

    struct NegativeBooleanEffectEntry : x3::position_tagged {
        BooleanReference reference;
    };

    struct UnchangedBooleanEffectEntry : x3::position_tagged {
        BooleanReference reference;
    };

    struct IncrementNumericalEffectEntry : x3::position_tagged {
        NumericalReference reference;
    };

    struct DecrementNumericalEffectEntry : x3::position_tagged {
        NumericalReference reference;
    };

    struct UnchangedNumericalEffectEntry : x3::position_tagged {
        NumericalReference reference;
    };

    struct FeatureEffectEntry : x3::position_tagged,
        x3::variant<
            x3::forward_ast<PositiveBooleanEffectEntry>,
            x3::forward_ast<NegativeBooleanEffectEntry>,
            x3::forward_ast<UnchangedBooleanEffectEntry>,
            x3::forward_ast<IncrementNumericalEffectEntry>,
            x3::forward_ast<DecrementNumericalEffectEntry>,
            x3::forward_ast<UnchangedNumericalEffectEntry>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    /* Rules */
    struct LoadRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<FeatureEffectEntry> feature_effects;
        RegisterReference register_reference;
        ConceptReference concept_reference;
    };

    struct ModuleReference : x3::position_tagged {
        Name reference;
    };

    struct CallRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<FeatureEffectEntry> feature_effects;
        ModuleReference module_reference;
        std::vector<RegisterReference> register_references;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<FeatureEffectEntry> feature_effects;
        ActionReference action_reference;
        std::vector<RegisterReference> register_references;
    };

    struct SearchRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<FeatureEffectEntry> feature_effects;
    };

    struct RuleEntry : x3::position_tagged,
        x3::variant<
            x3::forward_ast<LoadRuleEntry>,
            x3::forward_ast<CallRuleEntry>,
            x3::forward_ast<ActionRuleEntry>,
            x3::forward_ast<SearchRuleEntry>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Rules : x3::position_tagged {
        std::vector<RuleEntry> rules;
    };

    /* Sketch */
    struct ExtendedSketch : x3::position_tagged {
        NameEntry name;
        MemoryStatesEntry memory_states;
        RegistersEntry registers;
        BooleansEntry booleans;
        NumericalsEntry numericals;
        ConceptsEntry concepts;
        Rules rules;
    };
}}


#endif