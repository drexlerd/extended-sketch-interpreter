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

static std::string parse(const stage_1::ast::Name& node, const error_handler_type&, Context&) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}

static std::string parse(const stage_1::ast::NameEntry& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.name, error_handler, context);
}

static MemoryState parse(const stage_1::ast::MemoryStateDefinition& node, const error_handler_type& error_handler, Context& context) {
    return context.memory_state_factory.make_memory_state(parse(node.key, error_handler, context));
}

static MemoryState parse(const stage_1::ast::MemoryStateReference& node, const error_handler_type& error_handler, Context& context) {
    auto key = parse(node.key, error_handler, context);
    auto memory_state = context.memory_state_factory.get_memory_state(key);
    if (!memory_state) {
        error_handler(node, "Undefined memory state " + key);
        throw std::runtime_error("Unsuccessful parse.");
    }
    return memory_state;
}

static MemoryStateMap parse(const stage_1::ast::MemoryStatesEntry& node, const error_handler_type& error_handler, Context& context) {
    MemoryStateMap memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = parse(child, error_handler, context);
        memory_states.emplace(memory_state->get_key(), memory_state);
    }
    return memory_states;
}

static MemoryState parse(const stage_1::ast::InitialMemoryStateEntry& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}

static Register parse(const stage_1::ast::RegisterDefinition& node, const error_handler_type& error_handler, Context& context) {
    return context.register_factory.make_register(parse(node.key, error_handler, context));
}

static Register parse(const stage_1::ast::RegisterReference& node, const error_handler_type& error_handler, Context& context) {
    auto key = parse(node.key, error_handler, context);
    auto register_ = context.register_factory.get_register(key);
    if (!register_) {
        error_handler(node, "Undefined register " + key);
        throw std::runtime_error("Unsuccessful parse.");
    }
    return register_;
}

static RegisterMap parse(const stage_1::ast::RegistersEntry& node, const error_handler_type& error_handler, Context& context) {
    RegisterMap registers;
    for (const auto& child : node.definitions) {
        auto register_ = parse(child, error_handler, context);
        registers.emplace(register_->get_key(), register_);
    }
    return registers;
}

static MemoryState parse(const stage_1::ast::MemoryConditionEntry& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}

static MemoryState parse(const stage_1::ast::MemoryEffectEntry& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}


static LoadRule parse(const stage_1::ast::LoadRuleEntry& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto register_ = parse(node.register_reference, error_handler, context);
    auto concept_ = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concept_reference, error_handler, context.dlplan_context);
    return context.sketch_factory->make_load_rule(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}

static std::string parse(const stage_1::ast::ModuleReference& node, const error_handler_type& error_handler, Context& context) {
    // TODO: add check whether the module exists in a second stage?
    return parse(node.reference, error_handler, context);
}

static CallRule parse(const stage_1::ast::CallRuleEntry& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto module_ = parse(node.module_reference, error_handler, context);
    RegisterList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(parse(register_node, error_handler, context));
    }
    return context.sketch_factory->make_call_rule(memory_condition, memory_effect, feature_conditions, feature_effects, module_, registers);
}

static mimir::formalism::ActionSchema parse(const stage_1::ast::ActionReference& node, const error_handler_type& error_handler, Context& context) {
    auto action_name = parse(node.reference, error_handler, context);
    auto it = context.action_schema_map.find(action_name);
    if (it == context.action_schema_map.end()) {
        error_handler(node.reference, "undefined action schema " + action_name);
    }
    return it->second;
}

static ActionRule parse(const stage_1::ast::ActionRuleEntry& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto action_schema = parse(node.action_reference, error_handler, context);
    RegisterList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(parse(register_node, error_handler, context));
    }
    return context.sketch_factory->make_action_rule(memory_condition, memory_effect, feature_conditions, feature_effects, action_schema, registers);
}

static SearchRule parse(const stage_1::ast::SearchRuleEntry& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    return context.sketch_factory->make_search_rule(memory_condition, memory_effect, feature_conditions, feature_effects);
}


class RuleEntryVisitor {
private:
    Context& context;
    const error_handler_type& error_handler;

public:
    boost::variant<LoadRule, CallRule, ActionRule, SearchRule> result;

    RuleEntryVisitor(const error_handler_type& error_handler, Context& context)
        : context(context), error_handler(error_handler) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context);
    }
};

static boost::variant<LoadRule, CallRule, ActionRule, SearchRule>
parse(const stage_1::ast::RuleEntry& node, const error_handler_type& error_handler, Context& context) {
    RuleEntryVisitor visitor(error_handler, context);
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
    RuleVisitor(const error_handler_type& error_handler, Context& context,
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
parse(const stage_1::ast::Rules& node, const error_handler_type& error_handler, Context& context) {
    auto load_rules = LoadRuleList();
    auto call_rules = CallRuleList();
    auto action_rules = ActionRuleList();
    auto search_rules = SearchRuleList();
    RuleVisitor visitor(error_handler, context, load_rules, call_rules, action_rules, search_rules);
    for (const auto& rule_node : node.rules) {
        auto rule = parse(rule_node, error_handler, context);
        boost::apply_visitor(visitor, rule);
    }
    return {load_rules, call_rules, action_rules, search_rules};
}

ExtendedSketch parse(const stage_1::ast::ExtendedSketch& node, const error_handler_type& error_handler, Context& context) {
    auto name = parse(node.name, error_handler, context);
    auto memory_states = parse(node.memory_states, error_handler, context);
    auto initial_memory_state = parse(node.initial_memory_state, error_handler, context);
    auto registers = parse(node.registers, error_handler, context);
    auto booleans = dlplan::policy::parsers::policy::stage_2::parser::parse(node.booleans, error_handler, context.dlplan_context);
    auto numericals = dlplan::policy::parsers::policy::stage_2::parser::parse(node.numericals, error_handler, context.dlplan_context);
    auto concepts = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concepts, error_handler, context.dlplan_context);
    auto [load_rules, call_rules, action_rules, search_rules] = parse(node.rules, error_handler, context);
    return create_extended_sketch(
        name,
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules);
}

}