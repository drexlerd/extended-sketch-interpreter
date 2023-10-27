#include "parser.hpp"

#include <sstream>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_2/parser.hpp"
#include "src/extended_sketch/memory_state.hpp"
#include "src/extended_sketch/register.hpp"
#include "src/extended_sketch/rules.hpp"
#include "src/extended_sketch/extended_sketch.hpp"
#include "src/extended_sketch/signature.hpp"

using namespace dlplan::common::parsers;
using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2::parser {

static std::string parse(const stage_1::ast::Name& node, const error_handler_type&, Context&, SymbolTable& symbol_table) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}


static ArgumentRegister parse(const stage_1::ast::ArgumentRegister& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    return ArgumentRegister(
        node.type_name,
        parse(node.value_name, error_handler, context, symbol_table));
}

static ArgumentConcept parse(const stage_1::ast::ArgumentConcept& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    return ArgumentConcept(
        node.type_name,
        parse(node.value_name, error_handler, context, symbol_table));
}

class ArgumentVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;
    SymbolTable* symbol_table;

public:
    Argument result;

    ArgumentVisitor(const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table)
        : error_handler(error_handler), context(context), symbol_table(&symbol_table) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context, *symbol_table);
    }
};

static Argument parse(const stage_1::ast::Argument& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    ArgumentVisitor visitor(error_handler, context, symbol_table);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


static Signature parse(const stage_1::ast::Signature& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    const auto name = parse(node.name, error_handler, context, symbol_table);
    ArgumentList arguments;
    for (const auto& child_node : node.arguments) {
        arguments.push_back(parse(child_node, error_handler, context, symbol_table));
    }
    return Signature(name, arguments);
}

static MemoryStateHandle parse(const stage_1::ast::MemoryState& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    const auto key = parse(node.key, error_handler, context, symbol_table);
    const auto handle = symbol_table.memory_states.get_handle(key);
    if (handle != MemoryStateHandle::undefined) {
        error_handler(node, "Multiple definitions of memory state " + key);
        throw std::runtime_error("Failed parse.");
    }
    return symbol_table.memory_states.register_symbol(key);
}

static MemoryStateHandle parse(const stage_1::ast::MemoryStateReference& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto key = parse(node.key, error_handler, context, symbol_table);
    const auto handle = symbol_table.memory_states.get_handle(key);
    if (handle == MemoryStateHandle::undefined) {
        error_handler(node, "Undefined memory state " + key);
        throw std::runtime_error("Failed parse.");
    }
    return handle;
}

static MemoryStateHandleList parse(const stage_1::ast::MemoryStates& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    MemoryStateHandleList memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = parse(child, error_handler, context, symbol_table);
        memory_states.push_back(memory_state);
    }
    return memory_states;
}

static MemoryStateHandle parse(const stage_1::ast::InitialMemoryState& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    return parse(node.reference, error_handler, context, symbol_table);
}

static RegisterHandle parse(const stage_1::ast::Register& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    const auto key = parse(node.key, error_handler, context, symbol_table);
    const auto handle = symbol_table.registers.get_handle(key);
    if (handle != RegisterHandle::undefined) {
        error_handler(node, "Multiple definitions of register " + key);
        throw std::runtime_error("Failed parse.");
    }
    return symbol_table.registers.register_symbol(key);
}

static RegisterHandle parse(const stage_1::ast::RegisterReference& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto key = parse(node.key, error_handler, context, symbol_table);
    const auto handle = symbol_table.registers.get_handle(key);
    if (handle == RegisterHandle::undefined) {
        error_handler(node, "Undefined register " + key);
        throw std::runtime_error("Failed parse.");
    }
    return handle;
}

static RegisterHandleList parse(const stage_1::ast::Registers& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    RegisterHandleList registers;
    for (const auto& child : node.definitions) {
        registers.push_back(parse(child, error_handler, context, symbol_table));
    }
    return registers;
}

static MemoryStateHandle parse(const stage_1::ast::MemoryCondition& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    return parse(node.reference, error_handler, context, symbol_table);
}

static MemoryStateHandle parse(const stage_1::ast::MemoryEffect& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    return parse(node.reference, error_handler, context, symbol_table);
}


static LoadRuleHandle parse(const stage_1::ast::LoadRule& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto memory_condition = parse(node.memory_condition, error_handler, context, symbol_table);
    auto memory_effect = parse(node.memory_effect, error_handler, context, symbol_table);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto register_ = parse(node.register_reference, error_handler, context, symbol_table);
    auto concept_ = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concept_reference, error_handler, context.dlplan_context);
    return symbol_table.load_rules.register_symbol(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}

static std::string parse(const stage_1::ast::ExtendedSketchReference& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    // TODO: add check whether the module exists in a second stage?
    return parse(node.reference, error_handler, context, symbol_table);
}

static CallRuleHandle parse(const stage_1::ast::CallRule& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto memory_condition = parse(node.memory_condition, error_handler, context, symbol_table);
    auto memory_effect = parse(node.memory_effect, error_handler, context, symbol_table);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto module_ = parse(node.extended_sketch_reference, error_handler, context, symbol_table);
    RegisterHandleList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(parse(register_node, error_handler, context, symbol_table));
    }
    return symbol_table.call_rules.register_symbol(memory_condition, memory_effect, feature_conditions, feature_effects, module_, registers);
}

static mimir::formalism::ActionSchema parse(const stage_1::ast::ActionReference& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto action_name = parse(node.reference, error_handler, context, symbol_table);
    auto it = context.action_schema_map.find(action_name);
    if (it == context.action_schema_map.end()) {
        error_handler(node.reference, "undefined action schema " + action_name);
    }
    return it->second;
}

static ActionRuleHandle parse(const stage_1::ast::ActionRule& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto memory_condition = parse(node.memory_condition, error_handler, context, symbol_table);
    auto memory_effect = parse(node.memory_effect, error_handler, context, symbol_table);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto action_schema = parse(node.action_reference, error_handler, context, symbol_table);
    RegisterHandleList registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(parse(register_node, error_handler, context, symbol_table));
    }
    return symbol_table.action_rules.register_symbol(memory_condition, memory_effect, feature_conditions, feature_effects, action_schema, registers);
}

static SearchRuleHandle parse(const stage_1::ast::SearchRule& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto memory_condition = parse(node.memory_condition, error_handler, context, symbol_table);
    auto memory_effect = parse(node.memory_effect, error_handler, context, symbol_table);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parsers::policy::stage_2::parser::parse(effect_node, error_handler, context.dlplan_context));
    }
    return symbol_table.search_rules.register_symbol(memory_condition, memory_effect, feature_conditions, feature_effects);
}


class RuleEntryVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;
    SymbolTable* symbol_table;

public:
    boost::variant<LoadRuleHandle, CallRuleHandle, ActionRuleHandle, SearchRuleHandle> result;

    RuleEntryVisitor(const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table)
        : error_handler(error_handler), context(context), symbol_table(&symbol_table) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context, *symbol_table);
    }
};

static boost::variant<LoadRuleHandle, CallRuleHandle, ActionRuleHandle, SearchRuleHandle>
parse(const stage_1::ast::Rule& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    RuleEntryVisitor visitor(error_handler, context, symbol_table);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


class RuleVisitor {
private:
    Context& context;
    const error_handler_type& error_handler;
    LoadRuleHandleList& load_rules;
    CallRuleHandleList& call_rules;
    ActionRuleHandleList& action_rules;
    SearchRuleHandleList& search_rules;

public:
    RuleVisitor(const error_handler_type& error_handler, Context& context,
    LoadRuleHandleList& load_rules, CallRuleHandleList& call_rules,
    ActionRuleHandleList& action_rules, SearchRuleHandleList& search_rules)
        : context(context), error_handler(error_handler),
          load_rules(load_rules), call_rules(call_rules),
          action_rules(action_rules), search_rules(search_rules) { }

    void operator()(const LoadRuleHandle& load_rule) {
        load_rules.push_back(load_rule);
    }

    void operator()(const CallRuleHandle& call_rule) {
        call_rules.push_back(call_rule);
    }

    void operator()(const ActionRuleHandle& action_rule) {
        action_rules.push_back(action_rule);
    }

    void operator()(const SearchRuleHandle& search_rule) {
        search_rules.push_back(search_rule);
    }
};

static std::tuple<LoadRuleHandleList, CallRuleHandleList, ActionRuleHandleList, SearchRuleHandleList>
parse(const stage_1::ast::Rules& node, const error_handler_type& error_handler, Context& context, SymbolTable& symbol_table) {
    auto load_rules = LoadRuleHandleList();
    auto call_rules = CallRuleHandleList();
    auto action_rules = ActionRuleHandleList();
    auto search_rules = SearchRuleHandleList();
    RuleVisitor visitor(error_handler, context, load_rules, call_rules, action_rules, search_rules);
    for (const auto& rule_node : node.rules) {
        auto rule = parse(rule_node, error_handler, context, symbol_table);
        boost::apply_visitor(visitor, rule);
    }
    return {load_rules, call_rules, action_rules, search_rules};
}

ExtendedSketchHandle parse(const stage_1::ast::ExtendedSketch& node, const error_handler_type& error_handler, Context& context, SymbolTable& parent_symbol_table) {
    auto symbol_table = std::make_unique<SymbolTable>();
    auto signature = parse(node.signature, error_handler, context, *symbol_table);
    auto memory_states = parse(node.memory_states, error_handler, context, *symbol_table);
    auto initial_memory_state = parse(node.initial_memory_state, error_handler, context, *symbol_table);
    auto registers = parse(node.registers, error_handler, context, *symbol_table);
    auto booleans = dlplan::policy::parsers::policy::stage_2::parser::parse(node.booleans, error_handler, context.dlplan_context);
    auto numericals = dlplan::policy::parsers::policy::stage_2::parser::parse(node.numericals, error_handler, context.dlplan_context);
    auto concepts = dlplan::policy::parsers::policy::stage_2::parser::parse(node.concepts, error_handler, context.dlplan_context);
    auto [load_rules, call_rules, action_rules, search_rules] = parse(node.rules, error_handler, context, *symbol_table);
    auto extended_sketch = parent_symbol_table.extended_sketches.register_symbol(
        std::move(symbol_table),
        signature,
        memory_states,
        initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules);
    return extended_sketch;
}

}