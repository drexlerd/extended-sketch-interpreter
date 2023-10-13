#ifndef SRC_PARSER_PARSER_DEF_HPP_
#define SRC_PARSER_PARSER_DEF_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "error_handler.hpp"
#include "parser_api.hpp"


namespace sketches::extended_sketch { namespace parser
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
    struct QuotedStringClass;
    struct NameEntryClass;
    struct MemoryStateDefinitionClass;
    struct MemoryStateReferenceClass;
    struct MemoryStatesEntryClass;
    struct InitialMemoryStateEntryClass;
    struct RegisterDefinitionClass;
    struct RegisterReferenceClass;
    struct RegistersEntryClass;
    struct BooleanDefinitionClass;
    struct BooleanReferenceClass;
    struct BooleansEntryClass;
    struct NumericalDefinitionClass;
    struct NumericalReferenceClass;
    struct NumericalsEntryClass;
    struct ConceptDefinitionClass;
    struct ConceptReferenceClass;
    struct ConceptsEntryClass;
    struct MemoryConditionEntryClass;
    struct MemoryEffectEntryClass;
    struct PositiveBooleanConditionEntryClass;
    struct NegativeBooleanConditionEntryClass;
    struct GreaterNumericalConditionEntryClass;
    struct EqualNumericalConditionEntryClass;
    struct PositiveBooleanEffectEntryClass;
    struct NegativeBooleanEffectEntryClass;
    struct UnchangedBooleanEffectEntryClass;
    struct IncrementNumericalEffectEntryClass;
    struct DecrementNumericalEffectEntryClass;
    struct UnchangedNumericalEffectEntryClass;
    struct FeatureConditionEntryClass;
    struct FeatureEffectEntryClass;
    struct LoadRuleEntryClass;
    struct ModuleReferenceClass;
    struct CallRuleEntryClass;
    struct ActionReferenceClass;
    struct ActionRuleEntryClass;
    struct SearchRuleEntryClass;
    struct RuleEntryClass;
    struct RulesClass;
    struct ExtendedSketchClass;


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    x3::rule<NameClass, ast::Name> const
        name = "name";

    x3::rule<QuotedStringClass, ast::QuotedString> const
        quoted_string = "quoted_string";

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

    x3::rule<RegisterDefinitionClass, ast::RegisterDefinition> const
        register_definition = "register_definition";

    x3::rule<RegisterReferenceClass, ast::RegisterReference> const
        register_reference = "register_reference";

    x3::rule<RegistersEntryClass, ast::RegistersEntry> const
        registers_entry = "registers_entry";

    x3::rule<BooleanDefinitionClass, ast::BooleanDefinition> const
        boolean_definition = "boolean_definition";

    x3::rule<BooleanReferenceClass, ast::BooleanReference> const
        boolean_reference = "boolean_reference";

    x3::rule<BooleansEntryClass, ast::BooleansEntry> const
        booleans_entry = "booleans_entry";

    x3::rule<NumericalDefinitionClass, ast::NumericalDefinition> const
        numerical_definition = "numerical_definition";

    x3::rule<NumericalReferenceClass, ast::NumericalReference> const
        numerical_reference = "numerical_reference";

    x3::rule<NumericalsEntryClass, ast::NumericalsEntry> const
        numericals_entry = "numericals_entry";

    x3::rule<ConceptDefinitionClass, ast::ConceptDefinition> const
        concept_definition = "concept_definition";

    x3::rule<ConceptReferenceClass, ast::ConceptReference> const
        concept_reference = "concept_reference";

    x3::rule<ConceptsEntryClass, ast::ConceptsEntry> const
        concepts_entry = "concepts_entry";

    x3::rule<MemoryConditionEntryClass, ast::MemoryConditionEntry> const
        memory_condition_entry = "memory_condition_entry";

    x3::rule<MemoryEffectEntryClass, ast::MemoryEffectEntry> const
        memory_effect_entry = "memory_effect_entry";

    x3::rule<PositiveBooleanConditionEntryClass, ast::PositiveBooleanConditionEntry> const
        positive_boolean_condition_entry = "positive_boolean_condition_entry";

    x3::rule<NegativeBooleanConditionEntryClass, ast::NegativeBooleanConditionEntry> const
        negative_boolean_condition_entry = "negative_boolean_condition_entry";

    x3::rule<GreaterNumericalConditionEntryClass, ast::GreaterNumericalConditionEntry> const
        greater_numerical_condition_entry = "greater_numerical_condition_entry";

    x3::rule<EqualNumericalConditionEntryClass, ast::EqualNumericalConditionEntry> const
        equal_numerical_condition_entry = "equal_numerical_condition_entry";

    x3::rule<PositiveBooleanEffectEntryClass, ast::PositiveBooleanEffectEntry> const
        positive_boolean_effect_entry = "positive_boolean_effect_entry";

    x3::rule<NegativeBooleanEffectEntryClass, ast::NegativeBooleanEffectEntry> const
        negative_boolean_effect_entry = "negative_boolean_effect_entry";

    x3::rule<UnchangedBooleanEffectEntryClass, ast::UnchangedBooleanEffectEntry> const
        unchanged_boolean_effect_entry = "unchanged_boolean_effect_entry";

    x3::rule<IncrementNumericalEffectEntryClass, ast::IncrementNumericalEffectEntry> const
        increment_numerical_effect_entry = "increment_numerical_effect_entry";

    x3::rule<DecrementNumericalEffectEntryClass, ast::DecrementNumericalEffectEntry> const
        decrement_numerical_effect_entry = "decrement_numerical_effect_entry";

    x3::rule<UnchangedNumericalEffectEntryClass, ast::UnchangedNumericalEffectEntry> const
        unchanged_numerical_effect_entry = "unchanged_numerical_effect_entry";

    x3::rule<FeatureConditionEntryClass, ast::FeatureConditionEntry> const
        feature_condition_entry = "feature_condition_entry";

    x3::rule<FeatureEffectEntryClass, ast::FeatureEffectEntry> const
        feature_effect_entry = "feature_effect_entry";

    x3::rule<LoadRuleEntryClass, ast::LoadRuleEntry> const
        load_rule_entry = "load_rule_entry";

    x3::rule<ModuleReferenceClass, ast::ModuleReference> const
        module_reference = "module_reference";

    x3::rule<CallRuleEntryClass, ast::CallRuleEntry> const
        call_rule_entry = "call_rule_entry";

    x3::rule<ActionReferenceClass, ast::ActionReference> const
        action_reference = "action_reference";

    x3::rule<ActionRuleEntryClass, ast::ActionRuleEntry> const
        action_rule_entry = "action_rule_entry";

    x3::rule<SearchRuleEntryClass, ast::SearchRuleEntry> const
        search_rule_entry = "search_rule_entry";

    x3::rule<RuleEntryClass, ast::RuleEntry> const
        rule_entry = "rule_entry";

    x3::rule<RulesClass, ast::Rules> const
        rules = "rules";

    extended_sketch_type const extended_sketch = "extended_sketch";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

/*
    const auto name_def = lit('(') > lit(":name") > lexeme[+(char_ - lit(')'))] > lit(')');

    const auto quoted_string__def = "";

    const auto memory_state_def = "";

    const auto memory_states_def = "";

    const auto reg_def = "";

    const auto regs_def = "";

    const auto boolean_def = "";

    const auto booleans_def = "";

    const auto conditions_def = lit('(') > lit(":conditions") > lit(')');

    const auto effects_def =  lit('(') > lit(":effects") > lit(')');

    const auto load_rule_def = lit('(') >> lit(":load_rule") > conditions > effects > lit(')');

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
*/

    const auto name_def = alpha >> *(alnum | char_('-') | char_('_'));
    const auto quoted_string_def = lexeme[lit('"') >> +(char_ - lit('"')) >> lit('"')];
    const auto name_entry_def = lit('(') > lit(":name") > name > lit(')');
    const auto memory_state_definition_def = name;
    const auto memory_state_reference_def = name;
    const auto memory_states_entry_def = lit('(') >> lit(":memory_states") > lit('(') > *memory_state_definition > lit(')') > lit(')');
    const auto initial_memory_state_entry_def = lit('(') >> lit(":initial_memory_state") > memory_state_reference > lit(')');
    const auto register_definition_def = name;
    const auto register_reference_def = name;
    const auto registers_entry_def = lit('(') >> lit(":registers") > lit('(') > *register_definition > lit(')') > lit(')');
    const auto boolean_definition_def = lit('(') >> name >> quoted_string >> lit(')');
    const auto boolean_reference_def = name;
    const auto booleans_entry_def = lit('(') >> lit(":booleans") > *boolean_definition > lit(')');
    const auto numerical_definition_def = lit('(') >> name >> quoted_string >> lit(')');
    const auto numerical_reference_def = name;
    const auto numericals_entry_def = lit('(') >> lit(":numericals") > *numerical_definition > lit(')');
    const auto concept_definition_def = lit('(') >> name >> quoted_string >> lit(')');
    const auto concept_reference_def = name;
    const auto concepts_entry_def = lit('(') >> lit(":concepts") > *concept_definition > lit(')');
    const auto memory_condition_entry_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');
    const auto memory_effect_entry_def = lit('(') >> lit(":memory") > memory_state_reference > lit(')');
    const auto positive_boolean_condition_entry_def = lit('(') >> lit(":c_b_pos") >> boolean_reference >> lit(')');
    const auto negative_boolean_condition_entry_def = lit('(') >> lit(":c_b_neg") >> boolean_reference >> lit(')');
    const auto greater_numerical_condition_entry_def = lit('(') >> lit(":c_n_gt") >> numerical_reference >> lit(')');
    const auto equal_numerical_condition_entry_def = lit('(') >> lit(":c_n_eq") >> numerical_reference >> lit(')');
    const auto positive_boolean_effect_entry_def = lit('(') >> lit(":e_b_pos") >> boolean_reference >> lit(')');
    const auto negative_boolean_effect_entry_def = lit('(') >> lit(":e_b_neg") >> boolean_reference >> lit(')');
    const auto unchanged_boolean_effect_entry_def = lit('(') >> lit(":e_b_bot") >> boolean_reference >> lit(')');
    const auto increment_numerical_effect_entry_def = lit('(') >> lit(":e_n_inc") >> numerical_reference >> lit(')');
    const auto decrement_numerical_effect_entry_def = lit('(') >> lit(":e_n_dec") >> numerical_reference >> lit(')');
    const auto unchanged_numerical_effect_entry_def = lit('(') >> lit(":e_n_bot") >> numerical_reference >> lit(')');
    const auto feature_condition_entry_def =
        positive_boolean_condition_entry | negative_boolean_condition_entry | greater_numerical_condition_entry | equal_numerical_condition_entry;
    const auto feature_effect_entry_def =
        positive_boolean_effect_entry | negative_boolean_effect_entry | unchanged_boolean_effect_entry | increment_numerical_effect_entry | decrement_numerical_effect_entry | unchanged_numerical_effect_entry;
    const auto load_rule_entry_def =
        lit('(') >> lit(":load_rule")
            >> lit('(') >> lit(":conditions") >> memory_condition_entry >> *feature_condition_entry >> lit(')')
            >> lit('(') >> lit(":effects") >> memory_effect_entry >> *feature_effect_entry >> lit('(') >> lit("load") >> lit('(') >> register_reference >> concept_reference >> lit(')') >> lit(')') >> lit(')')
        >> lit(')');
    const auto module_reference_def = name;
    const auto call_rule_entry_def =
        lit('(') >> lit(":call_rule")
            >> lit('(') >> lit(":conditions") >> memory_condition_entry >> *feature_condition_entry >> lit(')')
            >> lit('(') >> lit(":effects") >> memory_effect_entry >> *feature_effect_entry >> lit('(') >> module_reference >> lit('(') >> *register_reference >> lit(')') >> lit(')') >> lit(')')
        >> lit(')');
    const auto action_reference_def = name;
    const auto action_rule_entry_def =
        lit('(') >> lit(":action_rule")
            >> lit('(') >> lit(":conditions") >> memory_condition_entry >> *feature_condition_entry >> lit(')')
            >> lit('(') >> lit(":effects") >> memory_effect_entry >> *feature_effect_entry >> lit('(') >> action_reference >> lit('(') >> *register_reference >> lit(')') >> lit(')') >> lit(')')
        >> lit(')');
    const auto search_rule_entry_def =
        lit('(') >> lit(":search_rule")
            >> lit('(') >> lit(":conditions") >> memory_condition_entry >> *feature_condition_entry >> lit(')')
            >> lit('(') >> lit(":effects") >> memory_effect_entry >> *feature_effect_entry >> lit(')')
        >> lit(')');
    const auto rule_entry_def =
        load_rule_entry | call_rule_entry | action_rule_entry | search_rule_entry;
    const auto rules_def = *rule_entry;
    const auto extended_sketch_def = lit('(')
        > lit(":extended_sketch")
        >> name_entry
        >> memory_states_entry
        >> initial_memory_state_entry
        >> registers_entry
        // >> booleans_entry
        //>> numericals_entry
        //>> concepts_entry
        //>> rules
        > lit(')');

    BOOST_SPIRIT_DEFINE(name, quoted_string, name_entry,
        memory_state_definition, memory_state_reference, memory_states_entry, initial_memory_state_entry,
        register_definition, register_reference, registers_entry,
        boolean_definition, boolean_reference, booleans_entry,
        numerical_definition, numerical_reference, numericals_entry,
        concept_definition, concept_reference, concepts_entry,
        memory_condition_entry, memory_effect_entry,
        positive_boolean_condition_entry, negative_boolean_condition_entry, greater_numerical_condition_entry, equal_numerical_condition_entry,
        positive_boolean_effect_entry, negative_boolean_effect_entry, unchanged_boolean_effect_entry, increment_numerical_effect_entry, decrement_numerical_effect_entry, unchanged_numerical_effect_entry,
        feature_condition_entry, feature_effect_entry,
        load_rule_entry, module_reference, call_rule_entry, action_reference, action_rule_entry, search_rule_entry, rule_entry, rules,
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
    struct InitialMemoryStateEntryClass : x3::annotate_on_success {};
    struct RegisterDefinitionClass : x3::annotate_on_success {};
    struct RegisterReferenceClass : x3::annotate_on_success {};
    struct RegistersEntryClass : x3::annotate_on_success {};
    struct BooleanDefinitionClass : x3::annotate_on_success {};
    struct BooleanReferenceClass : x3::annotate_on_success {};
    struct BooleansEntryClass : x3::annotate_on_success {};
    struct ConceptDefinitionClass : x3::annotate_on_success {};
    struct ConceptReferenceClass : x3::annotate_on_success {};
    struct ConceptsEntryClass : x3::annotate_on_success {};
    struct MemoryConditionEntryClass : x3::annotate_on_success {};
    struct MemoryEffectEntryClass : x3::annotate_on_success {};
    struct PositiveBooleanConditionEntryClass : x3::annotate_on_success {};
    struct NegativeBooleanConditionEntryClass : x3::annotate_on_success {};
    struct GreaterNumericalConditionEntryClass : x3::annotate_on_success {};
    struct EqualNumericalConditionEntryClass : x3::annotate_on_success {};
    struct PositiveBooleanEffectEntryClass : x3::annotate_on_success {};
    struct NegativeBooleanEffectEntryClass : x3::annotate_on_success {};
    struct UnchangedBooleanEffectEntryClass : x3::annotate_on_success {};
    struct IncrementNumericalEffectEntryClass : x3::annotate_on_success {};
    struct DecrementNumericalEffectEntryClass : x3::annotate_on_success {};
    struct UnchangedNumericalEffectEntryClass : x3::annotate_on_success {};
    struct FeatureConditionEntryClass : x3::annotate_on_success {};
    struct FeatureEffectEntryClass : x3::annotate_on_success {};
    struct LoadRuleEntryClass : x3::annotate_on_success {};
    struct ModuleReferenceClass : x3::annotate_on_success {};
    struct CallRuleEntryClass : x3::annotate_on_success {};
    struct ActionReferenceClass : x3::annotate_on_success {};
    struct ActionRuleEntryClass : x3::annotate_on_success {};
    struct SearchRuleEntryClass : x3::annotate_on_success {};
    struct RuleEntryClass : x3::annotate_on_success {};
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