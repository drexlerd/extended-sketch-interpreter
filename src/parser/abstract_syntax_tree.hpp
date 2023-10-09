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


class ExtendedSketchNode : public ASTNode {
public:
    std::vector<NameNode*> memory_state_name_nodes;
    NameNode* initial_memory_state_name_node;
    std::vector<NameNode*> register_name_nodes;
    std::vector<NameAndStringNode*> boolean_name_and_string_nodes;
    std::vector<NameAndStringNode*> numerical_name_and_string_nodes;
    std::vector<NameAndStringNode*> concept_name_and_string_nodes;

    ExtendedSketchNode(
        const std::vector<NameNode*>& memory_state_name_nodes,
        NameNode* initial_memory_state_name_node,
        const std::vector<NameNode*>& register_name_nodes,
        const std::vector<NameAndStringNode*>& boolean_name_and_string_nodes,
        const std::vector<NameAndStringNode*>& numerical_name_and_string_nodes,
        const std::vector<NameAndStringNode*>& concept_name_and_string_nodes);
    ~ExtendedSketchNode() override;

    ExtendedSketch get_extended_sketch(Context& context) const;
};



}

#endif
