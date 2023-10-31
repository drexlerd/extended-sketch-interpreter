#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_DEF_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_DEF_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/syntactic/parser.hpp"

#include "error_handler.hpp"
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "parser_api.hpp"


namespace sketches::parsers::extended_sketch::stage_1 { namespace parser
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


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    name_type const name = "name";

    memory_state_type const memory_state = "memory_state";

    memory_state_reference_type const memory_state_reference = "memory_state_reference";

    memory_states_type const memory_states = "memory_states";

    initial_memory_state_type const initial_memory_state = "initial_memory_state";

    register_type const register_ = "register";

    register_reference_type const register_reference = "register_reference";

    registers_type const registers = "registers";

    memory_condition_type const memory_condition = "memory_condition";

    memory_effect_type const memory_effect = "memory_effect";

    load_rule_type const load_rule = "load_rule";

    argument_register_type const argument_register = "argument_register";

    argument_concept_type const argument_concept = "argument_concept";

    argument_type const argument = "argument";

    call_type const call = "call";

    call_rule_type const call_rule = "call_rule";

    action_reference_type const action_reference = "action_reference";

    action_rule_type const action_rule = "action_rule";

    search_rule_type const search_rule = "search_rule";

    rule_type const rule = "rule";

    rules_type const rules = "rules";

    extended_sketch_type const extended_sketch = "extended_sketch";

    extended_sketch_root_type const extended_sketch_root = "extended_sketch";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    const auto name_def = alpha >> lexeme[*(alnum | char_('-') | char_('_'))];

    const auto memory_state_def = name;
    const auto memory_state_reference_def = name;
    const auto memory_states_def = lit('(') >> lit(":memory_states") > lit('(') >> *memory_state > lit(')') > lit(')');
    const auto initial_memory_state_def = lit('(') >> lit(":initial_memory_state") > memory_state_reference > lit(')');

    const auto register__def = name;
    const auto register_reference_def = name;
    const auto registers_def = lit('(') >> lit(":registers") > lit('(') > *register_ > lit(')') > lit(')');

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
                > lit('(') > lit(":load") > lit('(') > register_reference > dlplan::policy::concept_reference() > lit(')') > lit(')')
            > lit(')')
        > lit(')');

    const auto argument_register_def = x3::string(":register") > name;
    const auto argument_concept_def = x3::string(":concept") > name;
    const auto argument_def = argument_register | argument_concept;
    const auto call_def = lit('(') >> lit(":call") > name > lit('(') >> argument % lit(',') > lit(')') > lit(')');
    const auto call_rule_def =
        lit('(') >> lit(":call_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
                > call
            > lit(')')
        > lit(')');

    const auto action_reference_def = name;
    const auto action_rule_def =
        lit('(') >> lit(":action_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::feature_effect()
                > lit('(') > action_reference > lit('(') > *register_reference > lit(')') > lit(')')
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
        >> registers
        >> dlplan::policy::booleans()
        >> dlplan::policy::numericals()
        >> dlplan::policy::concepts()
        >> rules
        > lit(')');
    const auto extended_sketch_root_def = extended_sketch;

    BOOST_SPIRIT_DEFINE(name,
        memory_state, memory_state_reference, memory_states, initial_memory_state,
        register_, register_reference, registers,
        memory_condition, memory_effect,
        load_rule,
        argument_register, argument_concept, argument, call, call_rule,
        action_reference, action_rule,
        search_rule,
        rule, rules,
        extended_sketch, extended_sketch_root)

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
    struct QuotedStringClass : x3::annotate_on_success {};
    struct MemoryStateClass : x3::annotate_on_success {};
    struct MemoryStateReferenceClass : x3::annotate_on_success {};
    struct MemoryStatesClass : x3::annotate_on_success {};
    struct InitialMemoryStateClass : x3::annotate_on_success {};
    struct RegisterClass : x3::annotate_on_success {};
    struct RegisterReferenceClass : x3::annotate_on_success {};
    struct RegistersClass : x3::annotate_on_success {};
    struct MemoryConditionClass : x3::annotate_on_success {};
    struct MemoryEffectClass : x3::annotate_on_success {};
    struct LoadRuleClass : x3::annotate_on_success {};
    struct ArgumentRegisterClass : x3::annotate_on_success {};
    struct ArgumentConceptClass : x3::annotate_on_success {};
    struct ArgumentClass : x3::annotate_on_success {};
    struct ArgumentsClass : x3::annotate_on_success {};
    struct CallClass : x3::annotate_on_success {};
    struct CallRuleClass : x3::annotate_on_success {};
    struct ActionReferenceClass : x3::annotate_on_success {};
    struct ActionRuleClass : x3::annotate_on_success {};
    struct SearchRuleClass : x3::annotate_on_success {};
    struct RuleClass : x3::annotate_on_success {};
    struct ExtendedSketchReferenceClass : x3::annotate_on_success {};
    struct ExtendedSketchClass : x3::annotate_on_success {};
    struct ExtendedSketchRootClass : x3::annotate_on_success, error_handler_extended_sketch {};
}}

namespace sketches::parsers::extended_sketch::stage_1
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


    parser::register_type const& register_() {
        return parser::register_;
    }

    parser::register_reference_type const& register_reference() {
        return parser::register_reference;
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


    parser::argument_register_type const& argument_register() {
        return parser::argument_register;
    }

    parser::argument_concept_type const& argument_concept() {
        return parser::argument_concept;
    }

    parser::argument_type const& argument() {
        return parser::argument;
    }

    parser::call_type const& call() {
        return parser::call;
    }

    parser::call_rule_type const& call_rule() {
        return parser::call_rule;
    }


    parser::action_reference_type const& action_reference() {
        return parser::action_reference;
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
}

#endif