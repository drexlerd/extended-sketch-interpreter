#include "parser.hpp"

#include <sstream>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_2/parser.hpp"
#include "src/extended_sketch/memory_state.hpp"
#include "src/extended_sketch/register.hpp"
#include "src/extended_sketch/rules.hpp"
#include "src/extended_sketch/extended_sketch.hpp"

using namespace dlplan::common::parsers;


namespace sketches::parsers::extended_sketch::stage_2::parser {

static std::string translate(Context&, const error_handler_type&, const stage_1::ast::Name& node) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}

static std::string translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::NameEntry& node) {
    return translate(context, error_handler, node.name);
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::MemoryStateDefinition& node) {
    return context.memory_state_factory.make_memory_state(translate(context, error_handler, node.key));
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::MemoryStateReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto memory_state = context.memory_state_factory.get_memory_state(key);
    if (!memory_state) {
        error_handler(node, "Undefined memory state " + key);
        throw std::runtime_error("Unsuccessful parse.");
    }
    return memory_state;
}

static MemoryStateMap translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::MemoryStatesEntry& node) {
    MemoryStateMap memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = translate(context, error_handler, child);
        memory_states.emplace(memory_state->get_key(), memory_state);
    }
    return memory_states;
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::InitialMemoryStateEntry& node) {
    return translate(context, error_handler, node.reference);
}

static Register translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::RegisterDefinition& node) {
    return context.register_factory.make_register(translate(context, error_handler, node.key));
}

static Register translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::RegisterReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto register_ = context.register_factory.get_register(key);
    if (!register_) {
        error_handler(node, "Undefined register " + key);
        throw std::runtime_error("Unsuccessful parse.");
    }
    return register_;
}

static RegisterMap translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::RegistersEntry& node) {
    RegisterMap registers;
    for (const auto& child : node.definitions) {
        auto register_ = translate(context, error_handler, child);
        registers.emplace(register_->get_key(), register_);
    }
    return registers;
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::MemoryConditionEntry& node) {
    return translate(context, error_handler, node.reference);
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::MemoryEffectEntry& node) {
    return translate(context, error_handler, node.reference);
}


static LoadRule translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::LoadRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto register_ = translate(context, error_handler, node.register_reference);
    auto concept_ = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concept_reference, error_handler, context.dlplan_context);
    return create_load_rule(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}

static std::string translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::ModuleReference& node) {
    // TODO: add check whether the module exists in a second stage?
    return translate(context, error_handler, node.reference);
}

static CallRule translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::CallRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto module_ = translate(context, error_handler, node.module_reference);
    RegisterList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(translate(context, error_handler, register_node));
    }
    return create_call_rule(memory_condition, memory_effect, feature_conditions, feature_effects, module_, registers);
}

static mimir::formalism::ActionSchema translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::ActionReference& node) {
    auto action_name = translate(context, error_handler, node.reference);
    auto it = context.action_schema_map.find(action_name);
    if (it == context.action_schema_map.end()) {
        error_handler(node.reference, "undefined action schema " + action_name);
    }
    return it->second;
}

static ActionRule translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::ActionRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto action_schema = translate(context, error_handler, node.action_reference);
    RegisterList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(translate(context, error_handler, register_node));
    }
    return create_action_rule(memory_condition, memory_effect, feature_conditions, feature_effects, action_schema, registers);
}

static SearchRule translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::SearchRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    return create_iwsearch_rule(memory_condition, memory_effect, feature_conditions, feature_effects);
}


class RuleEntryVisitor {
private:
    Context& context;
    const error_handler_type& error_handler;

public:
    boost::variant<LoadRule, CallRule, ActionRule, SearchRule> result;

    RuleEntryVisitor(Context& context, const error_handler_type& error_handler)
        : context(context), error_handler(error_handler) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = translate(context, error_handler, node);
    }
};

static boost::variant<LoadRule, CallRule, ActionRule, SearchRule>
translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::RuleEntry& node) {
    RuleEntryVisitor visitor(context, error_handler);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


class RuleVisitor {
private:
    Context& context;
    const error_handler_type& error_handler;
    LoadRuleList& load_rules;
    CallRuleList& call_rules;
    ActionRuleList& action_rules;
    SearchRuleList& search_rules;

public:
    RuleVisitor(Context& context, const error_handler_type& error_handler,
    LoadRuleList& load_rules, CallRuleList& call_rules,
    ActionRuleList& action_rules, SearchRuleList& search_rules)
        : context(context), error_handler(error_handler),
          load_rules(load_rules), call_rules(call_rules),
          action_rules(action_rules), search_rules(search_rules) { }

    void operator()(const LoadRule& load_rule) {
        load_rules.push_back(load_rule);
    }

    void operator()(const CallRule& call_rule) {
        call_rules.push_back(call_rule);
    }

    void operator()(const ActionRule& action_rule) {
        action_rules.push_back(action_rule);
    }

    void operator()(const SearchRule& search_rule) {
        search_rules.push_back(search_rule);
    }
};

static std::tuple<LoadRuleList, CallRuleList, ActionRuleList, SearchRuleList>
translate(Context& context, const error_handler_type& error_handler, const stage_1::ast::Rules& node) {
    auto load_rules = LoadRuleList();
    auto call_rules = CallRuleList();
    auto action_rules = ActionRuleList();
    auto search_rules = SearchRuleList();
    RuleVisitor visitor(context, error_handler, load_rules, call_rules, action_rules, search_rules);
    for (const auto& rule_node : node.rules) {
        auto rule = translate(context, error_handler, rule_node);
        boost::apply_visitor(visitor, rule);
    }
    return {load_rules, call_rules, action_rules, search_rules};
}

ExtendedSketch parse_sketch(Context& context, const error_handler_type& error_handler, const stage_1::ast::ExtendedSketch& node) {
    auto name = translate(context, error_handler, node.name);
    auto memory_states = translate(context, error_handler, node.memory_states);
    auto initial_memory_state = translate(context, error_handler, node.initial_memory_state);
    auto registers = translate(context, error_handler, node.registers);
    auto booleans = dlplan::policy::parsers::policy::stage_2::parser::parse(node.booleans, error_handler, context.dlplan_context);
    auto numericals = dlplan::policy::parsers::policy::stage_2::parser::parse(node.numericals, error_handler, context.dlplan_context);
    auto concepts = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concepts, error_handler, context.dlplan_context);
    auto [load_rules, call_rules, action_rules, search_rules] = translate(context, error_handler, node.rules);
    return create_extended_sketch(
        name,
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules);
}

}