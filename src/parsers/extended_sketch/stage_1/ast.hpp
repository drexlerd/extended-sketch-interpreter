#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_HPP_

#include <vector>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_1/ast.hpp"


namespace sketches::parsers::extended_sketch::stage_1::ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    namespace x3 = boost::spirit::x3;

    struct Name;
    struct NameEntry;
    struct MemoryStateDefinition;
    struct MemoryStateReference;
    struct MemoryStatesEntry;
    struct InitialMemoryStateEntry;
    struct RegisterDefinition;
    struct RegisterReference;
    struct RegistersEntry;
    struct MemoryConditionEntry;
    struct MemoryEffectEntry;
    struct LoadRuleEntry;
    struct ModuleReference;
    struct CallRuleEntry;
    struct ActionReference;
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

    struct InitialMemoryStateEntry : x3::position_tagged {
        MemoryStateReference reference;
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


    /* Arguments */
    struct ArgumentDefinitionRegister : x3::position_tagged {
        Name key;
    };

    struct ArgumentDefinitionConcept : x3::position_tagged {
        Name key;
    };

    struct ArgumentDefinition : x3::position_tagged,
        x3::variant<
            x3::forward_ast<ArgumentDefinitionRegister>,
            x3::forward_ast<ArgumentDefinitionConcept>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct ArgumentsEntry : x3::position_tagged {
        std::vector<ArgumentDefinition> definitions;
    };


    /* Condition and effects */
    struct MemoryConditionEntry : x3::position_tagged {
        MemoryStateReference reference;
    };

    struct MemoryEffectEntry : x3::position_tagged {
        MemoryStateReference reference;
    };


    /* Rules */
    struct LoadRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        RegisterReference register_reference;
        dlplan::policy::parsers::policy::stage_1::ast::ConceptReference concept_reference;
    };

    struct ModuleReference : x3::position_tagged {
        Name reference;
    };

    struct CallRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        ModuleReference module_reference;
        std::vector<RegisterReference> register_references;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        ActionReference action_reference;
        std::vector<RegisterReference> register_references;
    };

    struct SearchRuleEntry : x3::position_tagged {
        MemoryConditionEntry memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffectEntry memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
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
        InitialMemoryStateEntry initial_memory_state;
        ArgumentsEntry arguments;
        RegistersEntry registers;
        dlplan::policy::parsers::policy::stage_1::ast::BooleansEntry booleans;
        dlplan::policy::parsers::policy::stage_1::ast::NumericalsEntry numericals;
        dlplan::policy::parsers::policy::stage_1::ast::ConceptsEntry concepts;
        Rules rules;
    };
}


#endif