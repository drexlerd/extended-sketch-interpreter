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
    struct MemoryStateDefinitionClass;
    struct MemoryStateReferenceClass;
    struct MemoryStatesEntryClass;
    struct InitialMemoryStateEntryClass;
    struct ArgumentRegisterClass;
    struct ArgumentConceptClass;
    struct ArgumentVariantClass;
    struct ArgumentsEntryClass;
    struct RegisterDefinitionClass;
    struct RegisterReferenceClass;
    struct RegistersEntryClass;

    struct MemoryConditionEntryClass;
    struct MemoryEffectEntryClass;
    struct LoadRuleClass;
    struct ModuleReferenceClass;
    struct CallRuleClass;
    struct ActionReferenceClass;
    struct ActionRuleClass;
    struct SearchRuleClass;
    struct RuleVariantClass;
    struct RulesClass;
    struct ExtendedSketchClass;


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    x3::rule<NameClass, ast::Name> const
        name = "name";

    x3::rule<NameEntryClass, ast::NameEntry> const
        name_entry = "name_entry";

    x3::rule<MemoryStateDefinitionClass, ast::MemoryStateDefinition> const
        memory_state_definition = "memory_state_definition";

    x3::rule<MemoryStateReferenceClass, ast::MemoryStateReference> const
        memory_state_reference = "memory_state_reference";

    x3::rule<MemoryStatesEntryClass, ast::MemoryStatesEntry> const
        memory_states_entry = "memory_states_entry";

    x3::rule<InitialMemoryStateEntryClass, ast::InitialMemoryStateEntry> const
        initial_memory_state_entry = "initial_memory_state_entry";

    x3::rule<ArgumentRegisterClass, ast::ArgumentRegister> const
        argument_register = "argument_register";

    x3::rule<ArgumentConceptClass, ast::ArgumentConcept> const
        argument_concept = "argument_concept";

    x3::rule<ArgumentVariantClass, ast::ArgumentVariant> const
        argument_variant = "argument_variant";

    x3::rule<ArgumentsEntryClass, ast::Arguments> const
        arguments = "arguments";

    x3::rule<RegisterDefinitionClass, ast::RegisterDefinition> const
        register_definition = "register_definition";

    x3::rule<RegisterReferenceClass, ast::RegisterReference> const
        register_reference = "register_reference";

    x3::rule<RegistersEntryClass, ast::RegistersEntry> const
        registers_entry = "registers_entry";

    x3::rule<MemoryConditionEntryClass, ast::MemoryConditionEntry> const
        memory_condition_entry = "memory_condition_entry";

    x3::rule<MemoryEffectEntryClass, ast::MemoryEffectEntry> const
        memory_effect_entry = "memory_effect_entry";

    x3::rule<LoadRuleClass, ast::LoadRule> const
        load_rule = "load_rule";

    x3::rule<ModuleReferenceClass, ast::ModuleReference> const
        module_reference = "module_reference";

    x3::rule<CallRuleClass, ast::CallRule> const
        call_rule = "call_rule";

    x3::rule<ActionReferenceClass, ast::ActionReference> const
        action_reference = "action_reference";

    x3::rule<ActionRuleClass, ast::ActionRule> const
        action_rule = "action_rule";

    x3::rule<SearchRuleClass, ast::SearchRule> const
        search_rule = "search_rule";

    x3::rule<RuleVariantClass, ast::RuleVariant> const
        rule_variant = "rule_variant";

    x3::rule<RulesClass, ast::Rules> const
        rules = "rules";

    extended_sketch_type const extended_sketch = "extended_sketch";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    const auto name_def = alpha >> lexeme[*(alnum | char_('-') | char_('_'))];
    const auto name_entry_def = lit('(') >> lit(":name") > name > lit(')');

    const auto memory_state_definition_def = name;
    const auto memory_state_reference_def = name;
    const auto memory_states_entry_def = lit('(') >> lit(":memory_states") > lit('(') >> *memory_state_definition > lit(')') > lit(')');
    const auto initial_memory_state_entry_def = lit('(') >> lit(":initial_memory_state") > memory_state_reference > lit(')');

    const auto argument_register_def = lit('(') >> lit(":register") > name > lit(')');
    const auto argument_concept_def = lit('(') >> lit(":concept") > name > lit(')');
    const auto argument_variant_def = argument_register | argument_concept;
    const auto arguments_def = lit('(') >> lit(":arguments") >> *argument_variant > lit(')');

    const auto register_definition_def = name;
    const auto register_reference_def = name;
    const auto registers_entry_def = lit('(') >> lit(":registers") > lit('(') > *register_definition > lit(')') > lit(')');

    const auto memory_condition_entry_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');
    const auto memory_effect_entry_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');

    const auto load_rule_def =
        lit('(') >> lit(":load_rule")
            > lit('(') > lit(":conditions")
                > memory_condition_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition_entry()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect_entry()
                > lit('(') > lit("load") > lit('(') > register_reference > dlplan::policy::parsers::policy::stage_1::concept_reference() > lit(')') > lit(')')
            > lit(')')
        > lit(')');
    const auto module_reference_def = name;
    const auto call_rule_def =
        lit('(') >> lit(":call_rule")
            > lit('(') > lit(":conditions")
                > memory_condition_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition_entry()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect_entry()
                > lit('(') >> module_reference >> lit('(') >> *register_reference >> lit(')') >> lit(')')
            > lit(')')
        > lit(')');
    const auto action_reference_def = name;
    const auto action_rule_def =
        lit('(') >> lit(":action_rule")
            > lit('(') > lit(":conditions")
                > memory_condition_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition_entry()
            > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect_entry()
                > lit('(') > action_reference > lit('(') > *register_reference > lit(')') > lit(')')
            > lit(')')
        > lit(')');
    const auto search_rule_def =
        lit('(') >> lit(":search_rule")
            > lit('(') > lit(":conditions")
                > memory_condition_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_condition_entry() > lit(')')
            > lit('(') > lit(":effects")
                > memory_effect_entry
                >> *dlplan::policy::parsers::policy::stage_1::feature_effect_entry()
            > lit(')')
        > lit(')');
    const auto rule_variant_def =
        load_rule | call_rule | action_rule | search_rule;
    const auto rules_def = *rule_variant;
    const auto extended_sketch_def = lit('(')
        > lit(":extended_sketch")
        > name_entry
        > memory_states_entry
        > initial_memory_state_entry
        >> arguments
        >> registers_entry
        >> dlplan::policy::parsers::policy::stage_1::booleans_entry()
        >> dlplan::policy::parsers::policy::stage_1::numericals_entry()
        >> dlplan::policy::parsers::policy::stage_1::concepts_entry()
        >> rules
        > lit(')');

    BOOST_SPIRIT_DEFINE(name, name_entry,
        memory_state_definition, memory_state_reference, memory_states_entry, initial_memory_state_entry,
        argument_register, argument_concept, argument_variant, arguments,
        register_definition, register_reference, registers_entry,
        memory_condition_entry, memory_effect_entry,
        load_rule, module_reference, call_rule, action_reference, action_rule, search_rule, rule_variant, rules,
        extended_sketch
    )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct NameClass : x3::annotate_on_success {};
    struct QuotedStringClass : x3::annotate_on_success {};
    struct NameEntryClass : x3::annotate_on_success {};
    struct MemoryStateDefinitionClass : x3::annotate_on_success {};
    struct MemoryStateReferenceClass : x3::annotate_on_success {};
    struct MemoryStatesEntryClass : x3::annotate_on_success {};
    struct ArgumentRegisterClass : x3::annotate_on_success {};
    struct ArgumentConceptClass : x3::annotate_on_success {};
    struct ArgumentVariantClass : x3::annotate_on_success {};
    struct ArgumentsClass : x3::annotate_on_success {};
    struct InitialMemoryStateEntryClass : x3::annotate_on_success {};
    struct RegisterDefinitionClass : x3::annotate_on_success {};
    struct RegisterReferenceClass : x3::annotate_on_success {};
    struct RegistersEntryClass : x3::annotate_on_success {};
    struct MemoryConditionEntryClass : x3::annotate_on_success {};
    struct MemoryEffectEntryClass : x3::annotate_on_success {};
    struct LoadRuleClass : x3::annotate_on_success {};
    struct ModuleReferenceClass : x3::annotate_on_success {};
    struct CallRuleClass : x3::annotate_on_success {};
    struct ActionReferenceClass : x3::annotate_on_success {};
    struct ActionRuleClass : x3::annotate_on_success {};
    struct SearchRuleClass : x3::annotate_on_success {};
    struct RuleVariantClass : x3::annotate_on_success {};
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