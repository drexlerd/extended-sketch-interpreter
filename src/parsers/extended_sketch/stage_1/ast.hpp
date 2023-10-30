#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_AST_HPP_

#include <string>
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
    struct MemoryState;
    struct MemoryStateReference;
    struct MemoryStates;
    struct InitialMemoryState;
    struct Register;
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
    struct Rule;
    struct Rules;
    struct ExtendedSketch;

    /* Basic character compounds */
    struct Name : x3::position_tagged {
        char alphabetical;
        std::string suffix;
    };


    /* Memory state entry and references */
    struct MemoryState : x3::position_tagged {
        Name key;
    };

    struct MemoryStateReference : x3::position_tagged {
        Name key;
    };

    struct MemoryStates : x3::position_tagged {
        std::vector<MemoryState> definitions;
    };

    struct InitialMemoryState : x3::position_tagged {
        MemoryStateReference reference;
    };


    /* Register entry and references */
    struct Register : x3::position_tagged {
        Name key;
    };

    struct RegisterReference : x3::position_tagged {
        Name key;
    };

    struct Registers : x3::position_tagged {
        std::vector<Register> definitions;
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
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffect> feature_effects;
        RegisterReference register_reference;
        dlplan::policy::parsers::policy::stage_1::ast::ConceptReference concept_reference;
    };

    struct ExtendedSketchReference : x3::position_tagged {
        Name reference;
    };

    struct ArgumentRegister : x3::position_tagged {
        std::string type_name;
        Name value_name;
    };

    struct ArgumentConcept : x3::position_tagged {
        std::string type_name;
        Name value_name;
    };

    struct Argument : x3::position_tagged,
        x3::variant<
            x3::forward_ast<ArgumentRegister>,
            x3::forward_ast<ArgumentConcept>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Call : x3::position_tagged {
        Name name;
        std::vector<Argument> arguments;
    };

    struct CallRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffect> feature_effects;
        Call call;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffect> feature_effects;
        ActionReference action_reference;
        std::vector<RegisterReference> register_references;
    };

    struct SearchRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::parsers::policy::stage_1::ast::FeatureEffect> feature_effects;
    };

    struct Rule : x3::position_tagged,
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
        MemoryStates memory_states;
        InitialMemoryState initial_memory_state;
        Registers registers;
        dlplan::policy::parsers::policy::stage_1::ast::Booleans booleans;
        dlplan::policy::parsers::policy::stage_1::ast::Numericals numericals;
        dlplan::policy::parsers::policy::stage_1::ast::Concepts concepts;
        Rules rules;
    };
}


#endif