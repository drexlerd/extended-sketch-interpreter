#ifndef SRC_PARSER_EMPLOYEE_DEF_HPP_
#define SRC_PARSER_EMPLOYEE_DEF_HPP_


#include "ast.hpp"
#include "ast_adapted.hpp"
#include "error_handler.hpp"
#include "rexpr.hpp"

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sketches::extended_sketch { namespace parser
{
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;

    using x3::lit;
    using x3::lexeme;

    using ascii::alnum;
    using ascii::char_;
    using ascii::string;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass;
    struct QuotedStringClass;
    struct MemoryStateClass;
    struct MemoryStatesClass;
    struct RegisterClass;
    struct RegistersClass;
    struct BooleanClass;
    struct BooleansClass;
    struct LoadRuleClass;
    struct CallRuleClass;
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

    x3::rule<QuotedStringClass, ast::QuotedString> const
        quoted_string_ = "quoted_string";  // TODO remove _

    x3::rule<MemoryStateClass, ast::MemoryState> const
        memory_state = "memory_state";

    x3::rule<MemoryStatesClass, ast::MemoryStates> const
        memory_states = "memory_states";

    x3::rule<RegisterClass, ast::Register> const
        reg = "memory_state";

    x3::rule<RegistersClass, ast::Registers> const
        regs = "registers";

    x3::rule<BooleanClass, ast::Boolean> const
        boolean = "boolean";

    x3::rule<BooleansClass, ast::Booleans> const
        booleans = "booleans";

    x3::rule<LoadRuleClass, ast::LoadRule> const
        load_rule = "load_rule";

    x3::rule<CallRuleClass, ast::CallRule> const
        call_rule = "call_rule";

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

    const auto name_def = lit('(') > lit(":name") > lexeme[+(char_ - lit(')'))] > lit(')');

    const auto quoted_string__def = "";

    const auto memory_state_def = "";

    const auto memory_states_def = "";

    const auto reg_def = "";

    const auto regs_def = "";

    const auto boolean_def = "";

    const auto booleans_def = "";

    const auto load_rule_def = lit('(') >> lit(":load_rule") >> lit(')');

    const auto call_rule_def = lit('(') >> lit(":call_rule") >> lit(')');

    const auto action_rule_def = lit('(') >> lit(":action_rule") >> lit(')');

    const auto search_rule_def = lit('(') >> lit(":search_rule") >> lit(')');

    const auto rule_def = load_rule | call_rule | action_rule | search_rule;

    const auto rules_def = *rule;

    const auto extended_sketch_def = lit('(')
        > lit(":extended_sketch")
        > name
        > rules
        > lit(')');

    BOOST_SPIRIT_DEFINE(name, quoted_string_, memory_state, memory_states, reg, regs, boolean, booleans, load_rule, call_rule, action_rule, search_rule, rule, rules, extended_sketch)

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
    struct QuotedStringClass : x3::annotate_on_success {};
    struct MemoryStateClass : x3::annotate_on_success {};
    struct MemoryStatesClass : x3::annotate_on_success {};
    struct RegisterClass : x3::annotate_on_success {};
    struct RegistersClass : x3::annotate_on_success {};
    struct BooleanClass : x3::annotate_on_success {};
    struct BooleansClass : x3::annotate_on_success {};
    struct LoadRuleClass : x3::annotate_on_success {};
    struct CallRuleClass : x3::annotate_on_success {};
    struct ActionRuleClass : x3::annotate_on_success {};
    struct SearchRuleClass : x3::annotate_on_success {};
    struct RuleClass : x3::annotate_on_success {};
    struct RulesClass : x3::annotate_on_success {};
    struct ExtendedSketchClass : x3::annotate_on_success, error_handler_base {};
}}

namespace sketches::extended_sketch
{
    parser::extended_sketch_type const& extended_sketch()
    {
        return parser::extended_sketch;
    }
}

#endif