#ifndef SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_DEF_HPP_
#define SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_DEF_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "../../dlplan/include/dlplan/policy/parsers/syntactic/parser.hpp"

#include "error_handler.hpp"
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser_api.hpp"


namespace mimir::extended_sketch { namespace parser
{
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;

    using x3::lit;
    using x3::lexeme;

    using ascii::alpha;
    using ascii::alnum;
    using ascii::char_;
    using ascii::string;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct ParameterRegisterClass;
    struct ParameterConceptClass;
    struct ParameterClass;
    struct SignatureClass;


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    name_type const name = "name";

    memory_state_type const memory_state = "memory_state";

    memory_state_reference_type const memory_state_reference = "memory_state_reference";

    memory_states_type const memory_states = "memory_states";

    initial_memory_state_type const initial_memory_state = "initial_memory_state";

    registers_type const registers = "registers";

    memory_condition_type const memory_condition = "memory_condition";

    memory_effect_type const memory_effect = "memory_effect";

    load_rule_type const load_rule = "load_rule";

    module_call_type const module_call = "module_call";

    call_rule_type const call_rule = "call_rule";

    action_reference_type const action_reference = "action_reference";

    action_call_type const action_call = "action_call";

    action_rule_type const action_rule = "action_rule";

    search_rule_type const search_rule = "search_rule";

    rule_type const rule = "rule";

    rules_type const rules = "rules";

    extended_sketch_type const extended_sketch = "extended_sketch";

    extended_sketch_root_type const extended_sketch_root = "extended_sketch";

    x3::rule<SignatureClass, ast::Signature> const
        signature = "signature";

    module_type const module_ = "module";

    module_root_type const module_root = "module";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    const auto name_def = alpha >> lexeme[*(alnum | char_('-') | char_('_'))];

    const auto memory_state_def = name;
    const auto memory_state_reference_def = name;
    const auto memory_states_def = lit('(') >> lit(":memory_states") > lit('(') >> *memory_state > lit(')') > lit(')');
    const auto initial_memory_state_def = lit('(') >> lit(":initial_memory_state") > memory_state_reference > lit(')');

    const auto registers_def = lit('(') >> lit(":registers") > -(lit('(') > *dlplan::policy::concept_definition() > lit(')')) > lit(')');

    const auto memory_condition_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');
    const auto memory_effect_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');

    const auto load_rule_def =
        lit('(') >> lit(":load_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
                > lit('(') > lit(":load") > lit('(') > dlplan::policy::concept_reference() > dlplan::policy::concept_reference() > lit(')') > lit(')')
            > lit(')')
        > lit(')');

    const auto module_call_def = 
        lit('(') >> lit(":call") > name 
            > lit('(') 
                >> -(lit('(') >> lit(":concepts") > -(lit('(') > *dlplan::policy::concept_reference() > lit(')'))> lit(')'))
                >> -(lit('(') >> lit(":roles") > -(lit('(') > *dlplan::policy::role_reference() > lit(')')) > lit(')'))
            > lit(')') 
        > lit(')');
    const auto call_rule_def =
        lit('(') >> lit(":call_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
                > module_call
            > lit(')')
        > lit(')');

    const auto action_reference_def = name;
    const auto action_call_def = lit('(') >> lit(":action") > action_reference > -(lit('(') >> *dlplan::policy::concept_reference() > lit(')')) > lit(')');
    const auto action_rule_def =
        lit('(') >> lit(":action_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
                > action_call
            > lit(')')
        > lit(')');

    const auto search_rule_def =
        lit('(') >> lit(":search_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition() > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
            > lit(')')
        > lit(')');

    const auto rule_def =
        load_rule | call_rule | action_rule | search_rule;
    const auto rules_def = *rule;

    const auto extended_sketch_def = lit('(')
        > lit(":extended_sketch")
        > memory_states
        > initial_memory_state
        > -registers
        > -dlplan::policy::booleans()
        > -dlplan::policy::numericals()
        > -dlplan::policy::concepts()
        > -dlplan::policy::roles()
        > rules
        > lit(')');
    const auto extended_sketch_root_def = extended_sketch;


    const auto signature_def = lit('(') >> lit(":signature")
        > name
            > lit('(')
                >> -(lit('(') >> lit(":concepts") > -(lit('(') > *dlplan::policy::concept_definition() > lit(')')) > lit(')'))
                >> -(lit('(') >> lit(":roles") > -(lit('(') > *dlplan::policy::role_definition() > lit(')')) > lit(')'))
            > lit(')') 
        > lit(')');

    const auto module__def = lit('(') >> lit(":module")
        > signature
        > extended_sketch
        > lit(')');
    const auto module_root_def = module_;


    BOOST_SPIRIT_DEFINE(name,
        memory_state, memory_state_reference, memory_states, initial_memory_state,
        registers,
        memory_condition, memory_effect,
        load_rule,
        module_call, call_rule,
        action_reference, action_call, action_rule,
        search_rule,
        rule, rules,
        extended_sketch, extended_sketch_root,
        signature, module_, module_root)

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
    struct MemoryStateClass : x3::annotate_on_success {};
    struct MemoryStateReferenceClass : x3::annotate_on_success {};
    struct MemoryStatesClass : x3::annotate_on_success {};
    struct InitialMemoryStateClass : x3::annotate_on_success {};
    struct RegistersClass : x3::annotate_on_success {};
    struct MemoryConditionClass : x3::annotate_on_success {};
    struct MemoryEffectClass : x3::annotate_on_success {};
    struct LoadRuleClass : x3::annotate_on_success {};
    struct ArgumentRegisterClass : x3::annotate_on_success {};
    struct ModuleCallClass : x3::annotate_on_success {};
    struct CallRuleClass : x3::annotate_on_success {};
    struct ActionReferenceClass : x3::annotate_on_success {};
    struct ActionCallClass : x3::annotate_on_success {};
    struct ActionRuleClass : x3::annotate_on_success {};
    struct SearchRuleClass : x3::annotate_on_success {};
    struct RuleClass : x3::annotate_on_success {};
    struct ExtendedSketchReferenceClass : x3::annotate_on_success {};
    struct ExtendedSketchClass : x3::annotate_on_success {};
    struct ExtendedSketchRootClass : x3::annotate_on_success, error_handler_extended_sketch {};

    struct SignatureClass : x3::annotate_on_success {};

    struct ModuleClass : x3::annotate_on_success {};
    struct ModuleRootClass : x3::annotate_on_success, error_handler_extended_module {};
}}

namespace mimir::extended_sketch
{
    parser::name_type const& name() {
        return parser::name;
    }

    parser::memory_state_type const& memory_state() {
        return parser::memory_state;
    }

    parser::memory_state_reference_type const& memory_state_reference() {
        return parser::memory_state_reference;
    }

    parser::memory_states_type const& memory_states() {
        return parser::memory_states;
    }

    parser::initial_memory_state_type const& initial_memory_state() {
        return parser::initial_memory_state;
    }

    parser::registers_type const& registers() {
        return parser::registers;
    }


    parser::memory_condition_type const& memory_condition() {
        return parser::memory_condition;
    }

    parser::memory_effect_type const& memory_effect() {
        return parser::memory_effect;
    }


    parser::load_rule_type const& load_rule() {
        return parser::load_rule;
    }


    parser::module_call_type const& module_call() {
        return parser::module_call;
    }

    parser::call_rule_type const& call_rule() {
        return parser::call_rule;
    }


    parser::action_reference_type const& action_reference() {
        return parser::action_reference;
    }

    parser::action_call_type const& action_call() {
        return parser::action_call;
    }

    parser::action_rule_type const& action_rule() {
        return parser::action_rule;
    }


    parser::search_rule_type const& search_rule() {
        return parser::search_rule;
    }


    parser::rule_type const& rule() {
        return parser::rule;
    }

    parser::rules_type const& rules() {
        return parser::rules;
    }


    parser::extended_sketch_type const& extended_sketch()
    {
        return parser::extended_sketch;
    }

    parser::extended_sketch_root_type const& extended_sketch_root()
    {
        return parser::extended_sketch_root;
    }


    parser::module_type const& module_() {
        return parser::module_;
    }

    parser::module_root_type const& module_root() {
        return parser::module_root;
    }
}

#endif