#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_DEF_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_DEF_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_1/parser.hpp"

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

    struct NameClass;
    struct NameEntryClass;
    struct MemoryStateClass;
    struct MemoryStateReferenceClass;
    struct MemoryStatesClass;
    struct InitialMemoryStateClass;
    struct ArgumentRegisterClass;
    struct ArgumentConceptClass;
    struct ArgumentClass;
    struct ArgumentsClass;
    struct RegisterClass;
    struct RegisterReferenceClass;
    struct RegistersClass;

    struct MemoryConditionClass;
    struct MemoryEffectClass;
    struct LoadRuleClass;
    struct ExtendedSketchReferenceClass;
    struct CallRuleClass;
    struct ActionReferenceClass;
    struct ActionRuleClass;
    struct SearchRuleClass;
    struct RuleClass;
    struct RulesClass;
    struct ExtendedSketchClass;


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    x3::rule<NameClass, ast::Name> const
        name = "name";

    x3::rule<NameEntryClass, ast::NameEntry> const
        name_entry = "name_entry";

    x3::rule<MemoryStateClass, ast::MemoryState> const
        memory_state = "memory_state";

    x3::rule<MemoryStateReferenceClass, ast::MemoryStateReference> const
        memory_state_reference = "memory_state_reference";

    x3::rule<MemoryStatesClass, ast::MemoryStates> const
        memory_states = "memory_states";

    x3::rule<InitialMemoryStateClass, ast::InitialMemoryState> const
        initial_memory_state = "initial_memory_state";

    x3::rule<ArgumentRegisterClass, ast::ArgumentRegister> const
        argument_register = "argument_register";

    x3::rule<ArgumentConceptClass, ast::ArgumentConcept> const
        argument_concept = "argument_concept";

    x3::rule<ArgumentClass, ast::Argument> const
        argument = "argument";

    x3::rule<ArgumentsClass, ast::Arguments> const
        arguments = "arguments";

    x3::rule<RegisterClass, ast::Register> const
        register_ = "register";

    x3::rule<RegisterReferenceClass, ast::RegisterReference> const
        register_reference = "register_reference";

    x3::rule<RegistersClass, ast::Registers> const
        registers = "registers";

    x3::rule<MemoryConditionClass, ast::MemoryCondition> const
        memory_condition = "memory_condition";

    x3::rule<MemoryEffectClass, ast::MemoryEffect> const
        memory_effect = "memory_effect";

    x3::rule<LoadRuleClass, ast::LoadRule> const
        load_rule = "load_rule";

    x3::rule<ExtendedSketchReferenceClass, ast::ExtendedSketchReference> const
        extended_sketch_reference = "extended_sketch_reference";

    x3::rule<CallRuleClass, ast::CallRule> const
        call_rule = "call_rule";

    x3::rule<ActionReferenceClass, ast::ActionReference> const
        action_reference = "action_reference";

    x3::rule<ActionRuleClass, ast::ActionRule> const
        action_rule = "action_rule";

    x3::rule<SearchRuleClass, ast::SearchRule> const
        search_rule = "search_rule";

    x3::rule<RuleClass, ast::Rule> const
        rule = "rule";

    x3::rule<RulesClass, ast::Rules> const
        rules = "rules";

    extended_sketch_type const extended_sketch = "extended_sketch";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    const auto name_def = alpha >> lexeme[*(alnum | char_('-') | char_('_'))];
    const auto name_entry_def = lit('(') >> lit(":name") > name > lit(')');

    const auto memory_state_def = name;
    const auto memory_state_reference_def = name;
    const auto memory_states_def = lit('(') >> lit(":memory_states") > lit('(') >> *memory_state > lit(')') > lit(')');
    const auto initial_memory_state_def = lit('(') >> lit(":initial_memory_state") > memory_state_reference > lit(')');

    const auto argument_register_def = lit('(') >> lit(":register") > name > lit(')');
    const auto argument_concept_def = lit('(') >> lit(":concept") > name > lit(')');
    const auto argument_def = argument_register | argument_concept;
    const auto arguments_def = lit('(') >> lit(":arguments") >> *argument > lit(')');

    const auto register__def = name;
    const auto register_reference_def = name;
    const auto registers_def = lit('(') >> lit(":registers") > lit('(') > *register_ > lit(')') > lit(')');

    const auto memory_condition_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');
    const auto memory_effect_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');

    const auto load_rule_def =
        lit('(') >> lit(":load_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect()
                > lit('(') > lit("load") > lit('(') > register_reference > dlplan::policy::parsers::policy::stage_1::concept_reference() > lit(')') > lit(')')
            > lit(')')
        > lit(')');
    const auto extended_sketch_reference_def = name;
    const auto call_rule_def =
        lit('(') >> lit(":call_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect()
                > lit('(') >> extended_sketch_reference >> lit('(') >> *register_reference >> lit(')') >> lit(')')
            > lit(')')
        > lit(')');
    const auto action_reference_def = name;
    const auto action_rule_def =
        lit('(') >> lit(":action_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect()
                > lit('(') > action_reference > lit('(') > *register_reference > lit(')') > lit(')')
            > lit(')')
        > lit(')');
    const auto search_rule_def =
        lit('(') >> lit(":search_rule")
            > lit('(') > lit(":conditions")
                > memory_condition
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition() > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect()
            > lit(')')
        > lit(')');
    const auto rule_def =
        load_rule | call_rule | action_rule | search_rule;
    const auto rules_def = *rule;
    const auto extended_sketch_def = lit('(')
        > lit(":extended_sketch")
        > name_entry
        > memory_states
        > initial_memory_state
        >> arguments
        >> registers
        >> dlplan::policy::parsers::policy::stage_1::booleans()
        >> dlplan::policy::parsers::policy::stage_1::numericals()
        >> dlplan::policy::parsers::policy::stage_1::concepts()
        >> rules
        > lit(')');

    BOOST_SPIRIT_DEFINE(name, name_entry,
        memory_state, memory_state_reference, memory_states, initial_memory_state,
        argument_register, argument_concept, argument, arguments,
        register_, register_reference, registers,
        memory_condition, memory_effect,
        load_rule, extended_sketch_reference, call_rule, action_reference, action_rule, search_rule, rule, rules,
        extended_sketch
    )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
    struct QuotedStringClass : x3::annotate_on_success {};
    struct NameEntryClass : x3::annotate_on_success {};
    struct MemoryStateClass : x3::annotate_on_success {};
    struct MemoryStateReferenceClass : x3::annotate_on_success {};
    struct MemoryStatesClass : x3::annotate_on_success {};
    struct ArgumentRegisterClass : x3::annotate_on_success {};
    struct ArgumentConceptClass : x3::annotate_on_success {};
    struct ArgumentClass : x3::annotate_on_success {};
    struct ArgumentsClass : x3::annotate_on_success {};
    struct InitialMemoryStateClass : x3::annotate_on_success {};
    struct RegisterClass : x3::annotate_on_success {};
    struct RegisterReferenceClass : x3::annotate_on_success {};
    struct RegistersClass : x3::annotate_on_success {};
    struct MemoryConditionClass : x3::annotate_on_success {};
    struct MemoryEffectClass : x3::annotate_on_success {};
    struct LoadRuleClass : x3::annotate_on_success {};
    struct CallRuleClass : x3::annotate_on_success {};
    struct ActionReferenceClass : x3::annotate_on_success {};
    struct ActionRuleClass : x3::annotate_on_success {};
    struct SearchRuleClass : x3::annotate_on_success {};
    struct RuleClass : x3::annotate_on_success {};
    struct ExtendedSketchReferenceClass : x3::annotate_on_success {};
    struct ExtendedSketchClass : x3::annotate_on_success, error_handler_extended_sketch {};
}}

namespace sketches::parsers::extended_sketch::stage_1
{
    parser::extended_sketch_type const& extended_sketch()
    {
        return parser::extended_sketch;
    }
}

#endif