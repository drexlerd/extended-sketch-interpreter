#ifndef SRC_PARSER_ABSTRACT_SYNTAX_TREE_HPP_
#define SRC_PARSER_ABSTRACT_SYNTAX_TREE_HPP_

#include <vector>

#include "../extended_sketch/declarations.hpp"
#include "../extended_sketch/memory_state_factory.hpp"

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

class MemoryStateMapNode : public ASTNode {
public:
    std::vector<NameNode*> name_nodes;

    MemoryStateMapNode(const std::vector<NameNode*>& name_nodes);
    ~MemoryStateMapNode() override;

    MemoryStateMap get_memory_state_map() const;
};

class RegisterMapNode : public ASTNode {
public:
    std::vector<NameNode*> name_nodes;

    RegisterMapNode(const std::vector<NameNode*>& name_nodes);
    ~RegisterMapNode() override;

    RegisterMap get_register_map() const;
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

};

class FeatureConditionNode : public ASTNode {

};

class PositiveBooleanConditionNode : public ASTNode {

};

class NegativeBooleanConditionNode : public ASTNode {

};

class GreaterNumericalConditionNode : public ASTNode {

};

class EqualNumericalConditionNode : public ASTNode {

};

class FeatureEffectNode : public ASTNode {

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

class LoadRuleNode : public ASTNode {
public:
    LoadRule get_load_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
};

class CallRuleNode : public ASTNode {
public:
    CallRule get_call_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
};

class ActionRuleNode : public ASTNode {
public:
    ActionRule get_action_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
};

class IWSearchRuleNode : public ASTNode {
public:
    NameNode* memory_condition_node;
    std::vector<FeatureConditionNode*> feature_condition_nodes;

    NameNode* memory_effect_node;
    std::vector<FeatureEffectNode*> feature_effect_nodes;

    IWSearchRuleNode(
        NameNode* memory_condition_node,
        const std::vector<FeatureConditionNode*>& feature_condition_nodes,
        NameNode* memory_effect_node,
        const std::vector<FeatureEffectNode*>& feature_effect_nodes);
    ~IWSearchRuleNode() override;

    IWSearchRule get_iwsearch_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
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

    LoadRule get_load_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
    CallRule get_call_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
    ActionRule get_action_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
    IWSearchRule get_iwsearch_rule(
        Context& context,
        const MemoryStateFactory& memory_states,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts) const;
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
