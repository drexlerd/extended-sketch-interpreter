#include "abstract_syntax_tree.hpp"

#include <sstream>

#include <boost/fusion/include/at_c.hpp>

#include "../extended_sketch/memory_state.hpp"
#include "../extended_sketch/register.hpp"
#include "../extended_sketch/rules.hpp"
#include "../extended_sketch/features.hpp"
#include "../extended_sketch/extended_sketch.hpp"


namespace sketches::extended_sketch::parser {

ASTNode::~ASTNode() = default;

/* CharacterNode */
CharacterNode::CharacterNode(char character) : character(character) {}


/* NameNode */
NameNode::NameNode(char prefix, const std::vector<CharacterNode*>& character_nodes) : prefix(prefix), character_nodes(character_nodes) {}

NameNode::~NameNode()
{
    for (auto node : character_nodes)
    {
        if (node)
        {
            delete node;
        }
    }
}

std::string NameNode::get_name() const
{
    std::vector<char> characters;
    characters.push_back(prefix);

    for (auto node : character_nodes)
    {
        characters.push_back(node->character);
    }

    return std::string(characters.begin(), characters.end());
}


/* StringNode */
StringNode::StringNode(const std::vector<CharacterNode*>& character_nodes)
    : character_nodes(character_nodes) { }

StringNode::~StringNode() {
    for (auto node : character_nodes) {
        delete node;
    }
}

std::string StringNode::get_string() const {
    std::stringstream ss;
    for (auto node : character_nodes) {
        ss << node->character;
    }
    return ss.str();
}


/* NameAndStringNode */
NameAndStringNode::NameAndStringNode(NameNode* name_node, StringNode* string_node)
    : name_node(name_node), string_node(string_node) { }

NameAndStringNode::~NameAndStringNode() {
    delete name_node;
    delete string_node;
}

std::pair<std::string, std::string> NameAndStringNode::get_name_and_string() const {
    return std::make_pair(name_node->get_name(), string_node->get_string());
}


/* MemoryConditionNode */
MemoryConditionNode::MemoryConditionNode(NameNode* memory_state_key)
    : memory_state_key(memory_state_key) { }

MemoryConditionNode::~MemoryConditionNode() {
    delete memory_state_key;
}

MemoryState MemoryConditionNode::get_memory_state(Context& context) const {
    return context.memory_state_factory.get_memory_state(memory_state_key->get_name());
}


/* FeatureConditionNode */
FeatureConditionNode::FeatureConditionNode(
    NameNode* boolean_key)
    : boolean_key(boolean_key) { }

FeatureConditionNode::~FeatureConditionNode() {
    delete boolean_key;
}


/* PositiveBooleanConditionNode */
PositiveBooleanConditionNode::PositiveBooleanConditionNode(
    NameNode* boolean_key) : FeatureConditionNode(boolean_key) { }

std::shared_ptr<const dlplan::policy::BaseCondition>
PositiveBooleanConditionNode::get_condition(Context& context) const {
    return context.policy_builder->add_pos_condition(context.boolean_factory.get_boolean(boolean_key->get_name())->get_boolean());
}


/* RuleNode */
RuleNode::RuleNode(
    MemoryConditionNode* memory_condition_node,
    MemoryConditionNode* memory_effect_node,
    const std::vector<FeatureConditionNode*>& feature_condition_nodes)
    : memory_condition_node(memory_condition_node),
      memory_effect_node(memory_effect_node),
      feature_condition_nodes(feature_condition_nodes) { }

RuleNode::~RuleNode() {
    delete memory_condition_node;
    delete memory_effect_node;
    for (auto node : feature_condition_nodes) {
        delete node;
    }
}

MemoryState RuleNode::get_memory_condition(Context& context) const {
    return memory_condition_node->get_memory_state(context);
}

MemoryState RuleNode::get_memory_effect(Context& context) const {
    return memory_effect_node->get_memory_state(context);
}

ConditionSet RuleNode::get_feature_conditions(Context& context) const {
    ConditionSet result;
    for (const auto& node : feature_condition_nodes) {
        result.insert(node->get_condition(context));
    }
    return result;
}


/* CallRuleNode */
CallRuleNode::CallRuleNode(
    MemoryConditionNode* memory_condition_node,
    MemoryConditionNode* memory_effect_node,
    const std::vector<FeatureConditionNode*>& feature_condition_nodes,
    NameNode* sketch_name_node,
    const std::vector<NameNode*>& register_name_nodes)
    : RuleNode(memory_condition_node, memory_effect_node, feature_condition_nodes),
      sketch_name_node(sketch_name_node),
      register_name_nodes(register_name_nodes) { }

CallRuleNode::~CallRuleNode() {
    delete sketch_name_node;
    for (auto& node : register_name_nodes) {
        delete node;
    }
}

CallRule CallRuleNode::get_call_rule(Context& context) const {
}


/* ActionRuleNode */
ActionRuleNode::ActionRuleNode(
    MemoryConditionNode* memory_condition_node,
    MemoryConditionNode* memory_effect_node,
    const std::vector<FeatureConditionNode*>& feature_condition_nodes,
    NameNode* action_name_node,
    const std::vector<NameNode*>& register_name_nodes)
    : RuleNode(memory_condition_node, memory_effect_node, feature_condition_nodes),
      action_name_node(action_name_node),
      register_name_nodes(register_name_nodes) { }

ActionRuleNode::~ActionRuleNode() {
    delete action_name_node;
    for (auto node : register_name_nodes) {
        delete node;
    }
}

ActionRule ActionRuleNode::get_action_rule(
    Context& context,
    const std::map<std::string, mimir::formalism::ActionSchema>& action_schemas) const {
    const auto name = action_name_node->get_name();
    auto it = action_schemas.find(name);
    if (it == action_schemas.end()) {
        throw std::runtime_error("ActionRuleNode::get_action_rule - no action schema exists with name " + name);
    }
}


/* IWSearchRuleNode */
IWSearchRuleNode::IWSearchRuleNode(
    MemoryConditionNode* memory_condition_node,
    MemoryConditionNode* memory_effect_node,
    const std::vector<FeatureConditionNode*>& feature_condition_nodes,
    const std::vector<FeatureEffectNode*>& feature_effect_nodes)
    : RuleNode(memory_condition_node, memory_effect_node, feature_condition_nodes),
      feature_effect_nodes(feature_effect_nodes) {
}

IWSearchRuleNode::~IWSearchRuleNode() {
    for (auto node : feature_effect_nodes) {
        delete node;
    }
}

IWSearchRule IWSearchRuleNode::get_iwsearch_rule(Context& context) const {
    EffectSet feature_effects;
    for (const auto& node : feature_effect_nodes) {
        feature_effects.insert(node->get_effect(context));
    }
    return create_iwsearch_rule(
        get_memory_condition(context),
        get_memory_effect(context),
        get_feature_conditions(context),
        feature_effects);
}



/* LoadCallActionOrIWSearchRuleNode */
LoadCallActionOrIWSearchRuleNode::LoadCallActionOrIWSearchRuleNode(LoadRuleNode* load_rule_node)
    : load_rule_node(load_rule_node),
      call_rule_node(nullptr),
      action_rule_node(nullptr),
      iwsearch_rule_node(nullptr) { }
LoadCallActionOrIWSearchRuleNode::LoadCallActionOrIWSearchRuleNode(CallRuleNode* call_rule_node)
    : load_rule_node(nullptr),
      call_rule_node(call_rule_node),
      action_rule_node(nullptr),
      iwsearch_rule_node(nullptr) { }
LoadCallActionOrIWSearchRuleNode::LoadCallActionOrIWSearchRuleNode(ActionRuleNode* action_rule_node)
    : load_rule_node(nullptr),
      call_rule_node(nullptr),
      action_rule_node(action_rule_node),
      iwsearch_rule_node(nullptr) { }
LoadCallActionOrIWSearchRuleNode::LoadCallActionOrIWSearchRuleNode(IWSearchRuleNode* iwsearch_rule_node)
    : load_rule_node(nullptr),
      call_rule_node(nullptr),
      action_rule_node(nullptr),
      iwsearch_rule_node(iwsearch_rule_node) { }

LoadCallActionOrIWSearchRuleNode::~LoadCallActionOrIWSearchRuleNode() {
    if (load_rule_node) delete load_rule_node;
    if (call_rule_node) delete call_rule_node;
    if (action_rule_node) delete action_rule_node;
    if (iwsearch_rule_node) delete iwsearch_rule_node;
}

LoadRule LoadCallActionOrIWSearchRuleNode::get_load_rule(Context& context) const {
    if (load_rule_node)
        return load_rule_node->get_load_rule(context);
    return nullptr;
}

CallRule LoadCallActionOrIWSearchRuleNode::get_call_rule(Context& context) const {
    if (call_rule_node)
        return call_rule_node->get_call_rule(context);
    return nullptr;
}

ActionRule LoadCallActionOrIWSearchRuleNode::get_action_rule(
    Context& context,
    const std::map<std::string, mimir::formalism::ActionSchema>& action_schemas) const {
    if (action_rule_node)
        return action_rule_node->get_action_rule(context, action_schemas);
    return nullptr;
}

IWSearchRule LoadCallActionOrIWSearchRuleNode::get_iwsearch_rule(Context& context) const {
    if (iwsearch_rule_node)
        return iwsearch_rule_node->get_iwsearch_rule(context);
    return nullptr;
}


/* ExtendedSketchNode */
ExtendedSketchNode::ExtendedSketchNode(
    NameNode* name_node,
    const std::vector<NameNode*>& memory_state_name_nodes,
    NameNode* initial_memory_state_name_node,
    const std::vector<NameNode*>& register_name_nodes,
    const std::vector<NameAndStringNode*>& boolean_name_and_string_nodes,
    const std::vector<NameAndStringNode*>& numerical_name_and_string_nodes,
    const std::vector<NameAndStringNode*>& concept_name_and_string_nodes,
    const std::vector<LoadCallActionOrIWSearchRuleNode*>& load_call_action_or_iwsearch_rule_nodes)
    : name_node(name_node),
      memory_state_name_nodes(memory_state_name_nodes),
      initial_memory_state_name_node(initial_memory_state_name_node),
      register_name_nodes(register_name_nodes),
      boolean_name_and_string_nodes(boolean_name_and_string_nodes),
      numerical_name_and_string_nodes(numerical_name_and_string_nodes),
      concept_name_and_string_nodes(concept_name_and_string_nodes),
      load_call_action_or_iwsearch_rule_nodes(load_call_action_or_iwsearch_rule_nodes) {}

ExtendedSketchNode::~ExtendedSketchNode() {
    delete name_node;
    for (auto node : memory_state_name_nodes) {
        delete node;
    }
    delete initial_memory_state_name_node;
    for (auto node : register_name_nodes) {
        delete node;
    }
    for (auto node : boolean_name_and_string_nodes) {
        delete node;
    }
    for (auto node : numerical_name_and_string_nodes) {
        delete node;
    }
    for (auto node : concept_name_and_string_nodes) {
        delete node;
    }
    for (auto node : load_call_action_or_iwsearch_rule_nodes) {
        delete node;
    }
}

ExtendedSketch ExtendedSketchNode::get_extended_sketch(Context& context) const {
    std::string name = name_node->get_name();
    MemoryStateMap memory_states;
    for (const auto& node : memory_state_name_nodes) {
        std::string name = node->get_name();
        memory_states.emplace(name, context.memory_state_factory.make_memory_state(name));
    }
    std::string initial_memory_state_key = initial_memory_state_name_node->get_name();
    auto find = memory_states.find(initial_memory_state_key);
    if (find == memory_states.end()) {
        throw std::runtime_error("ExtendedSketchNode::get_extended_sketch - initial memory state must be in memory state.");
    }
    MemoryState initial_memory_state = find->second;

    RegisterMap registers;
    for (const auto& node : register_name_nodes) {
        std::string name = node->get_name();
        registers.emplace(name, context.register_factory.make_register(name));
    }

    BooleanMap booleans;
    for (const auto& node : boolean_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        booleans.emplace(pair.first, context.boolean_factory.make_boolean(pair.first, pair.second));
    }
    NumericalMap numericals;
    for (const auto& node : numerical_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        numericals.emplace(pair.first, context.numerical_factory.make_numerical(pair.first, pair.second));
    }
    ConceptMap concepts;
    for (const auto& node : concept_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        concepts.emplace(pair.first, context.concept_factory.make_concept(pair.first, pair.second));
    }
    LoadRuleList load_rules;
    for (const auto& node : load_call_action_or_iwsearch_rule_nodes) {

    }
    CallRuleList call_rules;
    for (const auto& node : load_call_action_or_iwsearch_rule_nodes) {

    }
    const auto action_schemas = context.domain_description->get_action_schema_map();
    ActionRuleList action_rules;
    for (const auto& node : load_call_action_or_iwsearch_rule_nodes) {
        auto rule = node->get_action_rule(context, action_schemas);
        if (rule) action_rules.push_back(rule);
    }
    IWSearchRuleList iwsearch_rules;
    for (const auto& node : load_call_action_or_iwsearch_rule_nodes) {
        auto rule = node->get_iwsearch_rule(context);
        if (rule) iwsearch_rules.push_back(rule);
    }
    return make_extended_sketch(
            name,
            memory_states,
            initial_memory_state,
            registers,
            booleans,
            numericals,
            concepts,
            LoadRuleList(),
            CallRuleList(),
            ActionRuleList(),
            IWSearchRuleList());
}

}
