#ifndef SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_API_HPP_
#define SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_API_HPP_

#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"


namespace mimir::extended_sketch
{
    namespace x3 = boost::spirit::x3;

    ///////////////////////////////////////////////////////////////////////////
    // rexpr public interface
    ///////////////////////////////////////////////////////////////////////////
    namespace parser {
        struct NameClass;

        struct MemoryStateClass;
        struct MemoryStateReferenceClass;
        struct MemoryStatesClass;
        struct InitialMemoryStateClass;

        struct RegistersClass;

        struct MemoryConditionClass;
        struct MemoryEffectClass;

        struct LoadRuleClass;

        struct ModuleCallClass;
        struct CallRuleClass;

        struct ActionReferenceClass;
        struct ActionCallClass;
        struct ActionRuleClass;

        struct SearchRuleClass;

        struct RuleClass;
        struct RulesClass;

        struct ExtendedSketchClass;
        struct ExtendedSketchRootClass;

        struct ModuleClass;
        struct ModuleRootClass;


        typedef x3::rule<NameClass, ast::Name> name_type;

        typedef x3::rule<MemoryStateClass, ast::MemoryState> memory_state_type;
        typedef x3::rule<MemoryStateReferenceClass, ast::MemoryStateReference> memory_state_reference_type;
        typedef x3::rule<MemoryStatesClass, ast::MemoryStates> memory_states_type;
        typedef x3::rule<InitialMemoryStateClass, ast::InitialMemoryState> initial_memory_state_type;

        typedef x3::rule<RegistersClass, ast::Registers> registers_type;

        typedef x3::rule<MemoryConditionClass, ast::MemoryCondition> memory_condition_type;
        typedef x3::rule<MemoryEffectClass, ast::MemoryEffect> memory_effect_type;

        typedef x3::rule<LoadRuleClass, ast::LoadRule> load_rule_type;

        typedef x3::rule<ModuleCallClass, ast::ModuleCall> module_call_type;
        typedef x3::rule<CallRuleClass, ast::CallRule> call_rule_type;

        typedef x3::rule<ActionReferenceClass, ast::ActionReference> action_reference_type;
        typedef x3::rule<ActionCallClass, ast::ActionCall> action_call_type;
        typedef x3::rule<ActionRuleClass, ast::ActionRule> action_rule_type;

        typedef x3::rule<SearchRuleClass, ast::SearchRule> search_rule_type;

        typedef x3::rule<RuleClass, ast::Rule> rule_type;
        typedef x3::rule<RulesClass, ast::Rules> rules_type;

        typedef x3::rule<ExtendedSketchClass, ast::ExtendedSketch> extended_sketch_type;
        typedef x3::rule<ExtendedSketchRootClass, ast::ExtendedSketch> extended_sketch_root_type;

        typedef x3::rule<ModuleClass, ast::Module> module_type;
        typedef x3::rule<ModuleRootClass, ast::Module> module_root_type;


        BOOST_SPIRIT_DECLARE(
            name_type,
            memory_state_type, memory_state_reference_type, memory_states_type, initial_memory_state_type,
            registers_type,
            memory_condition_type, memory_effect_type,
            load_rule_type,
            module_call_type, call_rule_type,
            action_reference_type, action_call_type, action_rule_type,
            search_rule_type,
            rule_type, rules_type,
            extended_sketch_type, extended_sketch_root_type,
            module_type, module_root_type
        )
    }

    parser::name_type const& name();

    parser::memory_state_type const& memory_state();
    parser::memory_state_reference_type const& memory_state_reference();
    parser::memory_states_type const& memory_states();
    parser::initial_memory_state_type const& initial_memory_state();

    parser::registers_type const& registers();

    parser::memory_condition_type const& memory_condition();
    parser::memory_effect_type const& memory_effect();

    parser::load_rule_type const& load_rule();

    parser::module_call_type const& module_call();
    parser::call_rule_type const& call_rule();

    parser::action_reference_type const& action_reference();
    parser::action_call_type const& action_call();
    parser::action_rule_type const& action_rule();

    parser::search_rule_type const& search_rule();

    parser::rule_type const& rule();
    parser::rules_type const& rules();

    parser::extended_sketch_type const& extended_sketch();
    parser::extended_sketch_root_type const& extended_sketch_root();

    parser::module_type const& module_();
    parser::module_root_type const& module_root();
}

#endif