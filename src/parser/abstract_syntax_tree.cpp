#include "abstract_syntax_tree.hpp"

#include <sstream>

#include <boost/fusion/include/at_c.hpp>

#include "../extended_sketch/memory_state_factory.hpp"
#include "../extended_sketch/memory_state.hpp"
#include "../extended_sketch/register.hpp"
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


/* MemoryStateMapNode */
MemoryStateMapNode::MemoryStateMapNode(const std::vector<NameNode*>& name_nodes)
    : name_nodes(name_nodes) { }

MemoryStateMapNode::~MemoryStateMapNode() {
    for (auto node : name_nodes) {
        delete node;
    }
}

MemoryStateMap MemoryStateMapNode::get_memory_state_map() const {
    MemoryStateMap result;
    for (const auto& node : name_nodes) {
        auto name = node->get_name();
        result.emplace(name, std::make_shared<MemoryStateImpl>(name));
    }
    return result;
}


/* RegisterMapNode */
RegisterMapNode::RegisterMapNode(const std::vector<NameNode*>& name_nodes)
    : name_nodes(name_nodes) { }

RegisterMapNode::~RegisterMapNode() {
    for (auto node : name_nodes) {
        delete node;
    }
}

RegisterMap RegisterMapNode::get_register_map() const {
    RegisterMap result;
    for (const auto& node : name_nodes) {
        auto name = node->get_name();
        result.emplace(name, std::make_shared<RegisterImpl>(name));
    }
    return result;
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


/* IWSearchRuleNode */
IWSearchRuleNode::IWSearchRuleNode(
    NameNode* memory_condition_node,
    const std::vector<FeatureConditionNode*>& feature_condition_nodes,
    NameNode* memory_effect_node,
    const std::vector<FeatureEffectNode*>& feature_effect_nodes)
    : memory_condition_node(memory_condition_node),
      feature_condition_nodes(feature_condition_nodes),
      memory_effect_node(memory_effect_node),
      feature_effect_nodes(feature_effect_nodes) {
}

IWSearchRuleNode::~IWSearchRuleNode() {
    delete memory_condition_node;
    for (auto node : feature_condition_nodes) {
        delete node;
    }
    delete memory_effect_node;
    for (auto node : feature_effect_nodes) {
        delete node;
    }
}

IWSearchRule IWSearchRuleNode::get_iwsearch_rule(
    Context& context,
    const MemoryStateFactory& memory_states,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts) const {
    MemoryState memory_state_condition = memory_states.get_memory_state(memory_condition_node->get_name());
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

LoadRule LoadCallActionOrIWSearchRuleNode::get_load_rule(
    Context& context,
    const MemoryStateFactory& memory_states,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts) const {
    if (load_rule_node)
        return load_rule_node->get_load_rule(context, memory_states, booleans, numericals, concepts);
    return nullptr;
}

CallRule LoadCallActionOrIWSearchRuleNode::get_call_rule(
    Context& context,
    const MemoryStateFactory& memory_states,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts) const {
    if (call_rule_node)
        return call_rule_node->get_call_rule(context, memory_states, booleans, numericals, concepts);
    return nullptr;
}
ActionRule LoadCallActionOrIWSearchRuleNode::get_action_rule(
    Context& context,
    const MemoryStateFactory& memory_states,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts) const {
    if (action_rule_node)
        return action_rule_node->get_action_rule(context, memory_states, booleans, numericals, concepts);
    return nullptr;
}

IWSearchRule LoadCallActionOrIWSearchRuleNode::get_iwsearch_rule(
    Context& context,
    const MemoryStateFactory& memory_states,
    const BooleanMap& booleans,
    const NumericalMap& numericals,
    const ConceptMap& concepts) const {
    if (iwsearch_rule_node)
        return iwsearch_rule_node->get_iwsearch_rule(context, memory_states, booleans, numericals, concepts);
    return nullptr;
}


/* ExtendedSketchNode */
ExtendedSketchNode::ExtendedSketchNode(
    const std::vector<NameNode*>& memory_state_name_nodes,
    NameNode* initial_memory_state_name_node,
    const std::vector<NameNode*>& register_name_nodes,
    const std::vector<NameAndStringNode*>& boolean_name_and_string_nodes,
    const std::vector<NameAndStringNode*>& numerical_name_and_string_nodes,
    const std::vector<NameAndStringNode*>& concept_name_and_string_nodes,
    const std::vector<LoadCallActionOrIWSearchRuleNode*>& load_call_action_or_iwsearch_rule_nodes)
    : memory_state_name_nodes(memory_state_name_nodes),
      initial_memory_state_name_node(initial_memory_state_name_node),
      register_name_nodes(register_name_nodes),
      boolean_name_and_string_nodes(boolean_name_and_string_nodes),
      numerical_name_and_string_nodes(numerical_name_and_string_nodes),
      concept_name_and_string_nodes(concept_name_and_string_nodes),
      load_call_action_or_iwsearch_rule_nodes(load_call_action_or_iwsearch_rule_nodes) {}

ExtendedSketchNode::~ExtendedSketchNode() {
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
    MemoryStateFactory memory_state_factory;
    MemoryStateMap memory_states;
    for (const auto& node : memory_state_name_nodes) {
        std::string name = node->get_name();
        memory_states.emplace(name, memory_state_factory.make_memory_state(name));
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
        registers.emplace(name, make_register(name));
    }

    BooleanMap booleans;
    for (const auto& node : boolean_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        booleans.emplace(pair.first, context.dlplan_element_factory->parse_boolean(pair.second));
    }
    NumericalMap numericals;
    for (const auto& node : numerical_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        numericals.emplace(pair.first, context.dlplan_element_factory->parse_numerical(pair.second));
    }
    ConceptMap concepts;
    for (const auto& node : concept_name_and_string_nodes) {
        auto pair = node->get_name_and_string();
        concepts.emplace(pair.first, context.dlplan_element_factory->parse_concept(pair.second));
    }
    LoadRuleList load_rules;
    for (const auto& node : load_call_action_or_iwsearch_rule_nodes) {

    }
    return make_extended_sketch(
            std::move(memory_states),
            std::move(initial_memory_state),
            std::move(registers),
            std::move(booleans),
            std::move(numericals),
            std::move(concepts),
            LoadRuleList(),
            CallRuleList(),
            ActionRuleList(),
            IWSearchRuleList());
}

}
