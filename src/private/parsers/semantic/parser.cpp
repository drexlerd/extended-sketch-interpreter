#include "parser.hpp"

#include <unordered_map>
#include <sstream>

#include "../../dlplan/include/dlplan/policy.h"
#include "../../dlplan/include/dlplan/policy/parsers/semantic/parser.hpp"
#include "../../extended_sketch/memory_state.hpp"
#include "../../extended_sketch/register.hpp"
#include "../../extended_sketch/rules.hpp"
#include "../../extended_sketch/extended_sketch.hpp"
#include "../../extended_sketch/module_call.hpp"
#include "../../extended_sketch/action_call.hpp"
#include "../../extended_sketch/signature.hpp"
#include "../../extended_sketch/module.hpp"
#include "../../extended_sketch/declarations.hpp"

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


static ConceptMap parse(const ast::Registers& node, const error_handler_type& error_handler, Context& context) {
    ConceptMap registers;
    for (const auto& child : node.definitions) {
        auto key = dlplan::policy::parse(child, error_handler, context.dlplan_context);
        int register_index = registers.size();

        auto concept = context.dlplan_context.policy_factory.make_concept(key,
            context.dlplan_context.policy_factory.get_element_factory()->make_register_concept(register_index));

        registers.emplace(key, concept);
        context.register_mapping.emplace(concept, register_index);
        context.dlplan_context.concepts.emplace(key, dlplan::policy::NamedConceptData{child, concept});
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
    auto register_ = dlplan::policy::parse(node.register_reference, error_handler, context.dlplan_context);
    auto concept_ = dlplan::policy::parse(node.concept_reference, error_handler, context.dlplan_context);
    return make_load_rule(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}


class ArgumentVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;
    ConceptList &concept_arguments;
    RoleList &role_arguments;

public:
    ArgumentVisitor(const error_handler_type& error_handler_, Context& context_, ConceptList &concept_arguments_, RoleList &role_arguments_)
        : error_handler(error_handler_), context(context_), concept_arguments(concept_arguments_), role_arguments(role_arguments_) { }

    void operator()(const dlplan::policy::ast::ConceptReference& node) const {
        concept_arguments.push_back(dlplan::policy::parse(node, error_handler, context.dlplan_context));
    }

    void operator()(const dlplan::policy::ast::RoleReference& node) const {
        role_arguments.push_back(dlplan::policy::parse(node, error_handler, context.dlplan_context));
    }
};

static ModuleCall parse(const ast::ModuleCall& node, const error_handler_type& error_handler, Context& context) {
    const auto name = parse(node.name, error_handler, context);
    ConceptList concept_arguments;
    RoleList role_arguments;
    for (const auto& child_node : node.arguments) {
        boost::apply_visitor(ArgumentVisitor(error_handler, context, concept_arguments, role_arguments), child_node);
    }
    return ModuleCall(name, concept_arguments, role_arguments);
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
    auto module_call = parse(node.call, error_handler, context);
    return make_call_rule(memory_condition, memory_effect, feature_conditions, feature_effects, module_call);
}

static mimir::formalism::ActionSchema parse(const ast::ActionReference& node, const error_handler_type& error_handler, Context& context) {
    auto action_name = parse(node.reference, error_handler, context);
    auto it = context.action_schema_map.find(action_name);
    if (it == context.action_schema_map.end()) {
        error_handler(node.reference, "undefined action schema " + action_name);
        throw std::runtime_error("Failed parse.");
    }
    return it->second;
}

static ActionCall parse(const ast::ActionCall& node, const error_handler_type& error_handler, Context& context) {
    auto action_schema = parse(node.reference, error_handler, context);
    ConceptList arguments;
    for (const auto& child_node : node.arguments) {
        arguments.push_back(dlplan::policy::parse(child_node, error_handler, context.dlplan_context));
    }
    if (action_schema->arity != arguments.size()) {
        error_handler(node, "mismatched number of arguments in action call.");
        throw std::runtime_error("Failed parse.");
    }
    return ActionCall(action_schema, arguments);
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
    auto action_call = parse(node.call, error_handler, context);
    return make_action_rule(memory_condition, memory_effect, feature_conditions, feature_effects, action_call);
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
    BooleanMap booleans;
    if (node.booleans.has_value()) {
        booleans = dlplan::policy::parse(node.booleans.value(), error_handler, context.dlplan_context);
    }
    NumericalMap numericals;
    if (node.numericals.has_value()) {
        numericals = dlplan::policy::parse(node.numericals.value(), error_handler, context.dlplan_context);
    }
    ConceptMap concepts;
    if (node.concepts.has_value()) {
        concepts = dlplan::policy::parse(node.concepts.value(), error_handler, context.dlplan_context);
    }
    RoleMap roles;
    if (node.roles.has_value()) {
        roles = dlplan::policy::parse(node.roles.value(), error_handler, context.dlplan_context);
    }

    auto [load_rules, call_rules, action_rules, search_rules] = parse(node.rules, error_handler, context);

    // Build sketches for external rules, one for each memory state
    std::cout << "Group search rules by memory state" << std::endl;
    std::unordered_map<MemoryState, std::vector<SearchRule>> search_rules_by_memory_state;
    for (const auto& search_rule : search_rules) {
        search_rules_by_memory_state[search_rule->get_memory_state_condition()].push_back(search_rule);
    }
    std::unordered_map<MemoryState, std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, SearchRule>> search_rule_by_rule_by_memory_state;
    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> sketches_by_memory_state;
    for (const auto& pair : search_rules_by_memory_state) {
        dlplan::policy::Rules sketch_rules;
        for (const auto& search_rule : pair.second) {
            auto sketch_rule = context.dlplan_context.policy_factory.make_rule(search_rule->get_feature_conditions(), search_rule->get_feature_effects());
            search_rule_by_rule_by_memory_state[pair.first][sketch_rule] = search_rule;
            sketch_rules.insert(sketch_rule);
        }
        auto sketch = context.dlplan_context.policy_factory.make_policy(sketch_rules);
        sketches_by_memory_state[pair.first] = sketch;
    }
    // Group loadrules by internal memory
    std::cout << "Group load rules by memory state" << std::endl;
    std::unordered_map<MemoryState, std::vector<LoadRule>> load_rules_by_memory_state;
    for (const auto& load_rule : load_rules) {
        load_rules_by_memory_state[load_rule->get_memory_state_condition()].push_back(load_rule);
    }
    return make_extended_sketch(
        memory_states, initial_memory_state,
        booleans, numericals, concepts, roles,
        load_rules, call_rules, action_rules, search_rules,
        sketches_by_memory_state,
        search_rule_by_rule_by_memory_state,
        load_rules_by_memory_state,
        context.register_mapping);
}


class ParameterVisitor {
private:
    const error_handler_type& error_handler;
    Context& context;
    ConceptList &concept_parameters;
    RoleList &role_parameters;

public:
    ParameterVisitor(const error_handler_type& error_handler_, Context& context_, ConceptList &concept_parameters_, RoleList &role_parameters_)
        : error_handler(error_handler_), context(context_), concept_parameters(concept_parameters_), role_parameters(role_parameters_) { }

    void operator()(const dlplan::policy::ast::ConceptDefinition& node) const {
        const auto key = dlplan::policy::parse(node, error_handler, context.dlplan_context);

        auto concept_ = context.dlplan_context.policy_factory.make_concept(key,
            context.dlplan_context.policy_factory.get_element_factory()->make_argument_concept(concept_parameters.size()));

        concept_parameters.push_back(concept_);

        context.dlplan_context.concepts.emplace(key, dlplan::policy::NamedConceptData{node, concept_});
    }

    void operator()(const dlplan::policy::ast::RoleDefinition& node) const {
        const auto key = dlplan::policy::parse(node, error_handler, context.dlplan_context);

        auto role_ = context.dlplan_context.policy_factory.make_role(key,
            context.dlplan_context.policy_factory.get_element_factory()->make_argument_role(role_parameters.size()));

        role_parameters.push_back(role_);

        context.dlplan_context.roles.emplace(key, dlplan::policy::NamedRoleData{node, role_});
    }
};

static Signature parse(const ast::Signature& node, const error_handler_type& error_handler, Context& context) {
    const auto name = parse(node.name, error_handler, context);
    ConceptList concept_parameters;
    RoleList role_parameters;
    for (const auto& child_node : node.parameters) {
        boost::apply_visitor(ParameterVisitor(error_handler, context, concept_parameters, role_parameters), child_node);
    }
    return Signature(name, concept_parameters, role_parameters);
}

Module parse(const ast::Module& node, const dlplan::error_handler_type& error_handler, Context& context) {
    auto signature = parse(node.signature, error_handler, context);
    auto extended_sketch = parse(node.extended_sketch, error_handler, context);
    return make_module(signature, extended_sketch);
}


void resolve_function_calls(
    const ModuleList& modules) {
    std::unordered_map<std::string, Module> signature_to_module;
    for (const auto& module : modules) {
        std::stringstream signature_ss;
        signature_ss << module->get_signature().get_name() << " " << module->get_signature().get_concept_parameters().size() << " " << module->get_signature().get_role_parameters().size();
        signature_to_module[signature_ss.str()] = module;
    }
    for (auto& module : modules) {
        for (auto& call_rule : module->get_extended_sketch()->get_call_rules()) {
            std::stringstream call_ss;
            call_ss << call_rule->get_call().get_name() << " " << call_rule->get_call().get_concept_arguments().size()<< " " << call_rule->get_call().get_role_arguments().size();
            auto it = signature_to_module.find(call_ss.str());
            if (it == signature_to_module.end()) {
                // TODO: we want access to the error_handler and ast nodes here to point to the file.
                throw std::runtime_error("Could not resolve function call " + call_rule->get_call().compute_signature());
            }
            call_rule->set_callee(it->second);
        }
    }
}

}