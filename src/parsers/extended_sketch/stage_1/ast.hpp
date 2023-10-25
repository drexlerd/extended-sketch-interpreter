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
    struct MemoryStates;
    struct InitialMemoryState;
    struct RegisterDefinition;
    struct RegisterReference;
    struct Registers;
    struct MemoryCondition;
    struct MemoryEffect;
    struct LoadRule;
    struct ExtendedSketchReference;
    struct CallRule;
    struct ActionReference;
    struct ActionRule;
    struct SearchRule;
    struct RuleVariant;
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

    struct MemoryStates : x3::position_tagged {
        std::vector<MemoryStateDefinition> definitions;
    };

    struct InitialMemoryState : x3::position_tagged {
        MemoryStateReference reference;
    };


    /* Register entry and references */
    struct RegisterDefinition : x3::position_tagged {
        Name key;
    };

    struct RegisterReference : x3::position_tagged {
        Name key;
    };

    struct Registers : x3::position_tagged {
        std::vector<RegisterDefinition> definitions;
    };


    /* Arguments */
    struct ArgumentRegister : x3::position_tagged {
        Name key;
    };

    struct ArgumentConcept : x3::position_tagged {
        Name key;
    };

    struct ArgumentVariant : x3::position_tagged,
        x3::variant<
            x3::forward_ast<ArgumentRegister>,
            x3::forward_ast<ArgumentConcept>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Arguments : x3::position_tagged {
        std::vector<ArgumentVariant> definitions;
    };


    /* Condition and effects */
    struct MemoryCondition : x3::position_tagged {
        MemoryStateReference reference;
    };

    struct MemoryEffect : x3::position_tagged {
        MemoryStateReference reference;
    };


    /* Rules */
    struct LoadRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        RegisterReference register_reference;
        dlplan::policy::parsers::policy::stage_1::ast::ConceptReference concept_reference;
    };

    struct ExtendedSketchReference : x3::position_tagged {
        Name reference;
    };

    struct CallRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        ExtendedSketchReference extended_sketch_reference;
        std::vector<RegisterReference> register_references;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
        ActionReference action_reference;
        std::vector<RegisterReference> register_references;
    };

    struct SearchRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureConditionEntry> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffectEntry> feature_effects;
    };

    struct RuleVariant : x3::position_tagged,
        x3::variant<
            x3::forward_ast<LoadRule>,
            x3::forward_ast<CallRule>,
            x3::forward_ast<ActionRule>,
            x3::forward_ast<SearchRule>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Rules : x3::position_tagged {
        std::vector<RuleVariant> rules;
    };

    /* Sketch */
    struct ExtendedSketch : x3::position_tagged {
        NameEntry name;
        MemoryStates memory_states;
        InitialMemoryState initial_memory_state;
        Arguments arguments;
        Registers registers;
        dlplan::policy::parsers::policy::stage_1::ast::BooleansEntry booleans;
        dlplan::policy::parsers::policy::stage_1::ast::NumericalsEntry numericals;
        dlplan::policy::parsers::policy::stage_1::ast::ConceptsEntry concepts;
        Rules rules;
    };
}


#endif