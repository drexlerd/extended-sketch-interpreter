#ifndef SRC_PARSER_ABSTRACT_SYNTAX_TREE_HPP_
#define SRC_PARSER_ABSTRACT_SYNTAX_TREE_HPP_

#include <vector>

#include "../extended_sketch/declarations.hpp"

#include "context.hpp"


namespace sketches::extended_sketch::parser {
class ASTNode {
public:
    virtual ~ASTNode();
};

class CharacterNode : public ASTNode
{
    public:
    char character;

    CharacterNode(char character);
};

class NameNode : public ASTNode
{
    public:
    char prefix;
    std::vector<CharacterNode*> character_nodes;

    NameNode(char prefix, const std::vector<CharacterNode*>& character_nodes);
    ~NameNode() override;
    std::string get_name() const;
};

class StringNode : public ASTNode
{
public:
    std::vector<CharacterNode*> character_nodes;

    StringNode(const std::vector<CharacterNode*>& character_nodes);
    ~StringNode() override;
    std::string get_string() const;
};

class NameAndStringNode : public ASTNode {
public:
    NameNode* name_node;
    StringNode* string_node;

    NameAndStringNode(NameNode* name_node, StringNode* string_node);

    ~NameAndStringNode() override;

    std::pair<std::string, std::string> get_name_and_string() const;
};

class MemoryConditionNode : public ASTNode {
public:
    NameNode* memory_state_key;

    MemoryConditionNode(NameNode* memory_state_key);
    ~MemoryConditionNode() override;

    MemoryState get_memory_state(Context& context) const;
};


class FeatureConditionNode : public ASTNode {
public:
    NameNode* boolean_key;

    FeatureConditionNode(NameNode* boolean_key);
    ~FeatureConditionNode() override;

    virtual std::shared_ptr<const dlplan::policy::BaseCondition> get_condition(Context& context) const = 0;
};

class PositiveBooleanConditionNode : public FeatureConditionNode {
public:
    PositiveBooleanConditionNode(NameNode* boolean_key);

    std::shared_ptr<const dlplan::policy::BaseCondition> get_condition(Context& context) const override;
};

class NegativeBooleanConditionNode : public FeatureConditionNode {

};

class GreaterNumericalConditionNode : public FeatureConditionNode {

};

class EqualNumericalConditionNode : public FeatureConditionNode {

};

class FeatureEffectNode : public ASTNode {
public:
    NameNode* effect_type_node;
    NameNode* feature_key_node;

    FeatureEffectNode(NameNode* effect_type_node, NameNode* feature_key_node);
    ~FeatureEffectNode() override;

    virtual std::shared_ptr<const dlplan::policy::BaseEffect> get_effect(Context& context) const = 0;
};

class PositiveBooleanEffectNode : public FeatureEffectNode {

};

class NegativeBooleanEffectNode : public FeatureEffectNode {

};

class UnchangedBooleanEffectNode : public FeatureEffectNode {

};

class DecrementNumericalEffectNode : public FeatureEffectNode {

};

class IncrementNumericalEffectNode : public FeatureEffectNode {

};

class UnchangedNumericalEffectNode : public FeatureEffectNode {

};

class RuleNode : public ASTNode {
public:
    MemoryConditionNode* memory_condition_node;
    MemoryConditionNode* memory_effect_node;
    std::vector<FeatureConditionNode*> feature_condition_nodes;

    RuleNode(
        MemoryConditionNode* memory_condition_node,
        MemoryConditionNode* memory_effect_node,
        const std::vector<FeatureConditionNode*>& feature_condition_nodes);
    ~RuleNode();

    MemoryState get_memory_condition(Context& context) const;
    MemoryState get_memory_effect(Context& context) const;
    ConditionSet get_feature_conditions(Context& context) const;
};

class LoadRuleNode : public RuleNode {
public:
    LoadRule get_load_rule(Context& context) const;
};

class CallRuleNode : public RuleNode {
public:
    CallRule get_call_rule(Context& context) const;
};

class ActionRuleNode : public RuleNode {
public:
    NameNode* action_name_node;
    std::vector<NameNode*> register_name_nodes;

    ActionRuleNode(
        MemoryConditionNode* memory_condition_node,
        MemoryConditionNode* memory_effect_node,
        const std::vector<FeatureConditionNode*>& feature_condition_nodes,
        NameNode* action_name_node,
        const std::vector<NameNode*>& register_name_nodes);
    ~ActionRuleNode() override;

    ActionRule get_action_rule(
        Context& context,
        const std::map<std::string, mimir::formalism::ActionSchema>& action_schemas) const;
};

class IWSearchRuleNode : public RuleNode {
public:
    std::vector<FeatureEffectNode*> feature_effect_nodes;

    IWSearchRuleNode(
        MemoryConditionNode* memory_condition_node,
        MemoryConditionNode* memory_effect_node,
        const std::vector<FeatureConditionNode*>& feature_condition_nodes,
        const std::vector<FeatureEffectNode*>& feature_effect_nodes);
    ~IWSearchRuleNode() override;

    IWSearchRule get_iwsearch_rule(Context& context) const;
};

class LoadCallActionOrIWSearchRuleNode : public ASTNode {
public:
    LoadRuleNode* load_rule_node;
    CallRuleNode* call_rule_node;
    ActionRuleNode* action_rule_node;
    IWSearchRuleNode* iwsearch_rule_node;

    LoadCallActionOrIWSearchRuleNode(LoadRuleNode* load_rule_node);
    LoadCallActionOrIWSearchRuleNode(CallRuleNode* call_rule_node);
    LoadCallActionOrIWSearchRuleNode(ActionRuleNode* action_rule_node);
    LoadCallActionOrIWSearchRuleNode(IWSearchRuleNode* iwsearch_rule_node);
    ~LoadCallActionOrIWSearchRuleNode() override;

    LoadRule get_load_rule(Context& context) const;
    CallRule get_call_rule(Context& context) const;
    ActionRule get_action_rule(Context& context, const std::map<std::string, mimir::formalism::ActionSchema>& action_schemas) const;
    IWSearchRule get_iwsearch_rule(Context& context) const;
};


class ExtendedSketchNode : public ASTNode {
public:
    std::vector<NameNode*> memory_state_name_nodes;
    NameNode* initial_memory_state_name_node;
    std::vector<NameNode*> register_name_nodes;
    std::vector<NameAndStringNode*> boolean_name_and_string_nodes;
    std::vector<NameAndStringNode*> numerical_name_and_string_nodes;
    std::vector<NameAndStringNode*> concept_name_and_string_nodes;
    std::vector<LoadCallActionOrIWSearchRuleNode*> load_call_action_or_iwsearch_rule_nodes;

    ExtendedSketchNode(
        const std::vector<NameNode*>& memory_state_name_nodes,
        NameNode* initial_memory_state_name_node,
        const std::vector<NameNode*>& register_name_nodes,
        const std::vector<NameAndStringNode*>& boolean_name_and_string_nodes,
        const std::vector<NameAndStringNode*>& numerical_name_and_string_nodes,
        const std::vector<NameAndStringNode*>& concept_name_and_string_nodes,
        const std::vector<LoadCallActionOrIWSearchRuleNode*>& load_call_action_or_iwsearch_rule_nodes);
    ~ExtendedSketchNode() override;

    ExtendedSketch get_extended_sketch(Context& context) const;
};



}

#endif
