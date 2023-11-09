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

    x3::rule<ParameterRegisterClass, ast::ParameterRegister> const parameter_register = "parameter_register";

    x3::rule<ParameterConceptClass, ast::ParameterConcept> const parameter_concept = "parameter_concept";

    x3::rule<ParameterClass, ast::Parameter> const parameter = "parameter";

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

    const auto argument_register_def = lit(":register") > register_reference;
    const auto argument_concept_def = lit(":concept") > dlplan::policy::concept_reference();
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
                > lit('(') > lit(":action") > action_reference > lit('(') > *register_reference > lit(')') > lit(')')
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

    const auto parameter_register_def = lit(":register") > register_;
    const auto parameter_concept_def = lit(":concept") > dlplan::policy::concept_definition();
    const auto parameter_def = parameter_register | parameter_concept;
    const auto signature_def = lit('(') >> lit(":signature")
        > name
            > lit('(')
                >> -(parameter % lit(','))
            > lit(')')
        > lit(')');

    const auto module__def = lit('(') >> lit(":module")
        > signature
        > extended_sketch
        > lit(')');
    const auto module_root_def = module_;


    BOOST_SPIRIT_DEFINE(name,
        memory_state, memory_state_reference, memory_states, initial_memory_state,
        register_, register_reference, registers,
        memory_condition, memory_effect,
        load_rule,
        argument_register, argument_concept, argument, call, call_rule,
        action_reference, action_rule,
        search_rule,
        rule, rules,
        extended_sketch, extended_sketch_root,
        parameter_register, parameter_concept, parameter,
        signature, module_, module_root)

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
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

    struct ParameterRegisterClass : x3::annotate_on_success {};
    struct ParameterConceptClass : x3::annotate_on_success {};
    struct ParameterClass : x3::annotate_on_success {};
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


    parser::module_type const& module_() {
        return parser::module_;
    }

    parser::module_root_type const& module_root() {
        return parser::module_root;
    }
}

#endif