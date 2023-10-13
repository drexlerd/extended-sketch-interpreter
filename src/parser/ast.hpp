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
    struct Conditions;
    struct Effects;
    struct LoadRule;
    struct CallRule;
    struct ActionRule;
    struct SearchRule;
    struct Rule;
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

    struct FeatureCondition : x3::position_tagged,
        x3::variant<
            x3::forward_ast<PositiveBooleanConditionEntry>,
            x3::forward_ast<NegativeBooleanConditionEntry>,
            x3::forward_ast<GreaterNumericalConditionEntry>,
            x3::forward_ast<EqualNumericalConditionEntry>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct PositiveBooleanEffect : x3::position_tagged {
        BooleanReference reference;
    };

    struct NegativeBooleanEffect : x3::position_tagged {
        BooleanReference reference;
    };

    struct UnchangedBooleanEffect : x3::position_tagged {
        BooleanReference reference;
    };

    struct IncrementNumericalEffect : x3::position_tagged {
        NumericalReference reference;
    };

    struct DecrementNumericalEffect : x3::position_tagged {
        NumericalReference reference;
    };

    struct UnchangedNumericalEffect : x3::position_tagged {
        NumericalReference reference;
    };

    struct FeatureEffect : x3::position_tagged,
        x3::variant<
            x3::forward_ast<PositiveBooleanEffect>,
            x3::forward_ast<NegativeBooleanEffect>,
            x3::forward_ast<UnchangedBooleanEffect>,
            x3::forward_ast<IncrementNumericalEffect>,
            x3::forward_ast<DecrementNumericalEffect>,
            x3::forward_ast<UnchangedNumericalEffect>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct FeatureConditionsEntry : x3::position_tagged {
        std::vector<FeatureCondition> feature_conditions;
    };

    struct FeatureEffectsEntry : x3::position_tagged {
        std::vector<FeatureEffect> feature_effects;
    };

    /* Rules */
    struct LoadRule : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        FeatureConditionsEntry feature_conditions;
        MemoryEffectEntry memory_effect;
        RegisterReference register_reference;
        ConceptReference concept_reference;
        FeatureEffectsEntry feature_effects;
    };

    struct ModuleReference : x3::position_tagged {
        Name reference;
    };

    struct CallRule : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        FeatureConditionsEntry feature_conditions;
        MemoryEffectEntry memory_effect;
        ModuleReference module_reference;
        std::vector<RegisterReference> register_references;
        FeatureEffectsEntry feature_effects;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionRule : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        FeatureConditionsEntry feature_conditions;
        MemoryEffectEntry memory_effect;
        ActionReference action_reference;
        std::vector<RegisterReference> register_references;
        FeatureEffectsEntry feature_effects;
    };

    struct SearchRule : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        FeatureConditionsEntry feature_conditions;
        MemoryEffectEntry memory_effect;
        FeatureEffectsEntry feature_effects;
    };

    struct RuleEntry : x3::position_tagged,
        x3::variant<
            x3::forward_ast<LoadRule>,
            x3::forward_ast<CallRule>,
            x3::forward_ast<ActionRule>,
            x3::forward_ast<SearchRule>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Rules : x3::position_tagged {
        std::vector<Rule> rules;
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