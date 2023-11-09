#include "parser.hpp"

#include <sstream>

#include "../../dlplan/include/dlplan/policy.h"
#include "../../dlplan/include/dlplan/policy/parsers/semantic/parser.hpp"
#include "../../extended_sketch/memory_state.hpp"
#include "../../extended_sketch/register.hpp"
#include "../../extended_sketch/rules.hpp"
#include "../../extended_sketch/extended_sketch.hpp"
#include "../../extended_sketch/call.hpp"
#include "../../extended_sketch/signature.hpp"
#include "../../extended_sketch/module.hpp"
#include "../../extended_sketch/parameters.hpp"

using namespace dlplan;
using namespace mimir::extended_sketch;


namespace mimir::extended_sketch {

static std::string parse(const ast::Name& node, const error_handler_type&, Context&) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}



static MemoryState parse(const ast::MemoryState& node, const error_handler_type& error_handler, Context& context) {
    const auto key = parse(node.key, error_handler, context);
    const auto it = context.memory_states.find(key);
    if (it != context.memory_states.end()) {
        error_handler(node, "Multiple definitions of memory state " + key);
        error_handler(it->second.node, "Previous definition: ");
        throw std::runtime_error("Failed parse.");
    }
    return context.memory_states.emplace(key, Data<ast::MemoryState, MemoryState>{ node, make_memory_state(key) }).first->second.result;
}

static MemoryState parse(const ast::MemoryStateReference& node, const error_handler_type& error_handler, Context& context) {
    auto key = parse(node.key, error_handler, context);
    const auto it = context.memory_states.find(key);
    if (it == context.memory_states.end()) {
        error_handler(node, "Undefined memory state " + key);
        throw std::runtime_error("Failed parse.");
    }
    return it->second.result;
}

static MemoryStateMap parse(const ast::MemoryStates& node, const error_handler_type& error_handler, Context& context) {
    MemoryStateMap memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = parse(child, error_handler, context);
        memory_states.emplace(memory_state->compute_signature(), memory_state);
    }
    return memory_states;
}

static MemoryState parse(const ast::InitialMemoryState& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}

static Register parse(const ast::Register& node, const error_handler_type& error_handler, Context& context) {
    const auto key = parse(node.key, error_handler, context);
    const auto it = context.registers.find(key);
    if (it != context.registers.end()) {
        error_handler(node, "Multiple definitions of register " + key);
        error_handler(it->second.node, "Previous definition: ");
        throw std::runtime_error("Failed parse.");
    }
    return context.registers.emplace(key, Data<ast::Register, Register>{ node, make_register(key)} ).first->second.result;
}

static Register parse(const ast::RegisterReference& node, const error_handler_type& error_handler, Context& context) {
    auto key = parse(node.key, error_handler, context);
    const auto it = context.registers.find(key);
    if (it == context.registers.end()) {
        error_handler(node, "Undefined register " + key);
        throw std::runtime_error("Failed parse.");
    }
    return it->second.result;
}

static RegisterMap parse(const ast::Registers& node, const error_handler_type& error_handler, Context& context) {
    RegisterMap registers;
    for (const auto& child : node.definitions) {
        auto register_ = parse(child, error_handler, context);
        registers.emplace(register_->compute_signature(), register_);
    }
    return registers;
}

static MemoryState parse(const ast::MemoryCondition& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}

static MemoryState parse(const ast::MemoryEffect& node, const error_handler_type& error_handler, Context& context) {
    return parse(node.reference, error_handler, context);
}


static LoadRule parse(const ast::LoadRule& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto register_ = parse(node.register_reference, error_handler, context);
    auto concept_ = dlplan::policy::parse(node.concept_reference, error_handler, context.dlplan_context);
    return make_load_rule(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}

static ArgumentRegister parse(const ast::ArgumentRegister& node, const error_handler_type& error_handler, Context& context) {
    return ArgumentRegister(parse(node.reference, error_handler, context));
}

static ArgumentConcept parse(const ast::ArgumentConcept& node, const error_handler_type& error_handler, Context& context) {
    return ArgumentConcept(dlplan::policy::parse(node.reference, error_handler, context.dlplan_context));
}

class ArgumentVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;

public:
    Argument result;

    ArgumentVisitor(const error_handler_type& error_handler, Context& context)
        : error_handler(error_handler), context(context) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context);
    }
};

static Argument parse(const ast::Argument& node, const error_handler_type& error_handler, Context& context) {
    ArgumentVisitor visitor(error_handler, context);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}

static Call parse(const ast::Call& node, const error_handler_type& error_handler, Context& context) {
    const auto name = parse(node.name, error_handler, context);
    ArgumentList arguments;
    for (const auto& child_node : node.arguments) {
        arguments.push_back(parse(child_node, error_handler, context));
    }
    return Call(name, arguments);
}

static CallRule parse(const ast::CallRule& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto call = parse(node.call, error_handler, context);
    return make_call_rule(memory_condition, memory_effect, feature_conditions, feature_effects, call);
}

static mimir::formalism::ActionSchema parse(const ast::ActionReference& node, const error_handler_type& error_handler, Context& context) {
    auto action_name = parse(node.reference, error_handler, context);
    auto it = context.action_schema_map.find(action_name);
    if (it == context.action_schema_map.end()) {
        error_handler(node.reference, "undefined action schema " + action_name);
    }
    return it->second;
}

static ActionRule parse(const ast::ActionRule& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parse(effect_node, error_handler, context.dlplan_context));
    }
    auto action_schema = parse(node.action_reference, error_handler, context);
    std::vector<Register> registers;
    for (const auto& register_node : node.register_references) {
        registers.push_back(parse(register_node, error_handler, context));
    }
    return make_action_rule(memory_condition, memory_effect, feature_conditions, feature_effects, action_schema, registers);
}

static SearchRule parse(const ast::SearchRule& node, const error_handler_type& error_handler, Context& context) {
    auto memory_condition = parse(node.memory_condition, error_handler, context);
    auto memory_effect = parse(node.memory_effect, error_handler, context);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(dlplan::policy::parse(condition_node, error_handler, context.dlplan_context));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(dlplan::policy::parse(effect_node, error_handler, context.dlplan_context));
    }
    return make_search_rule(memory_condition, memory_effect, feature_conditions, feature_effects);
}


class RuleEntryVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;

public:
    boost::variant<LoadRule, CallRule, ActionRule, SearchRule> result;

    RuleEntryVisitor(const error_handler_type& error_handler, Context& context)
        : error_handler(error_handler), context(context) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context);
    }
};

static boost::variant<LoadRule, CallRule, ActionRule, SearchRule>
parse(const ast::Rule& node, const error_handler_type& error_handler, Context& context) {
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
parse(const ast::Rules& node, const error_handler_type& error_handler, Context& context) {
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

ExtendedSketch parse(const ast::ExtendedSketch& node, const error_handler_type& error_handler, Context& context) {
    auto memory_states = parse(node.memory_states, error_handler, context);
    auto initial_memory_state = parse(node.initial_memory_state, error_handler, context);
    auto registers = parse(node.registers, error_handler, context);
    auto booleans = dlplan::policy::parse(node.booleans, error_handler, context.dlplan_context);
    auto numericals = dlplan::policy::parse(node.numericals, error_handler, context.dlplan_context);
    auto concepts = dlplan::policy::parse(node.concepts, error_handler, context.dlplan_context);
    auto [load_rules, call_rules, action_rules, search_rules] = parse(node.rules, error_handler, context);
    return make_extended_sketch(
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules
    );
}


static ParameterRegister parse(const ast::ParameterRegister& node, const error_handler_type& error_handler, Context& context) {
    return ParameterRegister(parse(node.definition, error_handler, context));
}

static ParameterConcept parse(const ast::ParameterConcept& node, const error_handler_type& error_handler, Context& context) {
    const auto definition = parse(node.definition, error_handler, context.dlplan_context);
    const auto named_concept = context.dlplan_context.concepts.emplace(definition, dlplan::policy::NamedConceptData{ node.definition,
        context.dlplan_context.policy_factory.make_concept(definition, nullptr) }).first->second.result;
    return ParameterConcept(named_concept);
}

class ParameterVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;

public:
    Parameter result;

    ParameterVisitor(const error_handler_type& error_handler, Context& context)
        : error_handler(error_handler), context(context) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = parse(node, error_handler, context);
    }
};

static Parameter parse(const ast::Parameter& node, const error_handler_type& error_handler, Context& context) {
    ParameterVisitor visitor(error_handler, context);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


static Signature parse(const ast::Signature& node, const error_handler_type& error_handler, Context& context) {
    const auto name = parse(node.name, error_handler, context);
    ParameterList parameters;
    for (const auto& child_node : node.parameters) {
        parameters.push_back(parse(child_node, error_handler, context));
    }
    return Signature(name, parameters);
}

Module parse(const ast::Module& node, const dlplan::error_handler_type& error_handler, Context& context) {
    auto signature = parse(node.signature, error_handler, context);
    auto extended_sketch = parse(node.extended_sketch, error_handler, context);
    return make_module(signature, extended_sketch);
}


void resolve_function_calls(
    const ModuleList& modules) {
    for (const auto& module : modules) {
        for (const auto& call_rule : module->get_extended_sketch()->get_call_rules()) {
            std::cout << call_rule->m_call.compute_signature() << std::endl;

        }
    }
}

}