#ifndef SRC_PRIVATE_PARSERS_SYNTACTIC_AST_HPP_
#define SRC_PRIVATE_PARSERS_SYNTACTIC_AST_HPP_

#include <string>
#include <vector>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional.hpp>

#include "../../dlplan/include/dlplan/policy/parsers/syntactic/ast.hpp"


namespace mimir::extended_sketch::ast
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
    struct Registers : x3::position_tagged {
        std::vector<dlplan::policy::ast::ConceptDefinition> definitions;
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
        std::vector<dlplan::policy::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::ast::FeatureEffect> feature_effects;
        dlplan::policy::ast::ConceptReference register_reference;
        dlplan::policy::ast::ConceptReference concept_reference;
    };

    struct ExtendedSketchReference : x3::position_tagged {
        Name reference;
    };


    struct ModuleCall : x3::position_tagged {
        Name name;
        std::vector<boost::variant<dlplan::policy::ast::ConceptReference, dlplan::policy::ast::RoleReference>> arguments;
    };

    struct CallRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::ast::FeatureEffect> feature_effects;
        ModuleCall call;
    };

    struct ActionReference : x3::position_tagged {
        Name reference;
    };

    struct ActionCall : x3::position_tagged {
        ActionReference reference;
        std::vector<dlplan::policy::ast::ConceptReference> arguments;
    };

    struct ActionRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::ast::FeatureEffect> feature_effects;
        ActionCall call;
    };

    struct SearchRule : x3::position_tagged {
        MemoryCondition memory_condition;
        std::vector<dlplan::policy::ast::FeatureCondition> feature_conditions;
        MemoryEffect memory_effect;
        std::vector<dlplan::policy::ast::FeatureEffect> feature_effects;
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
        boost::optional<dlplan::policy::ast::Booleans> booleans;
        boost::optional<dlplan::policy::ast::Numericals> numericals;
        boost::optional<dlplan::policy::ast::Concepts> concepts;
        boost::optional<dlplan::policy::ast::Roles> roles;
        Rules rules;
    };


    /* Signature entry */
    struct Signature : x3::position_tagged {
        Name name;
        std::vector<boost::variant<dlplan::policy::ast::ConceptDefinition, dlplan::policy::ast::RoleDefinition>> parameters;
    };

    struct Module : x3::position_tagged {
        Signature signature;
        ExtendedSketch extended_sketch;
    };
}


#endif