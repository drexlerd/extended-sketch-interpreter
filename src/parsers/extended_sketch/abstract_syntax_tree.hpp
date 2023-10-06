#ifndef SRC_PARSERS_EXTENDED_SKETCH_ABSTRACT_SYNTAX_TREE_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_ABSTRACT_SYNTAX_TREE_HPP_

#include <vector>

#include "../../extended_sketch/declarations.hpp"

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

class BooleanNode : public ASTNode {
public:
    NameNode* key;
    StringNode* repr;

    BooleanNode(NameNode* key, StringNode* repr);
    ~BooleanNode() override;

    std::pair<std::string, std::shared_ptr<const dlplan::core::Boolean>> get_boolean(Context& context) const;
};

class BooleanListNode : public ASTNode {
public:
    std::vector<BooleanNode*> boolean_nodes;

    BooleanListNode(const std::vector<BooleanNode*>& boolean_nodes);
    ~BooleanListNode() override;
    BooleanMap get_boolean_map(Context& context) const;
};

class NumericalNode : public ASTNode {
public:
    NameNode* key;
    StringNode* repr;

    NumericalNode(NameNode* key, StringNode* repr);
    ~NumericalNode() override;

    std::pair<std::string, std::shared_ptr<const dlplan::core::Numerical>> get_numerical(Context& context) const;
};

class NumericalListNode : public ASTNode {
public:
    std::vector<NumericalNode*> numerical_nodes;

    NumericalListNode(const std::vector<NumericalNode*>& numerical_nodes);
    ~NumericalListNode() override;
    NumericalMap get_numerical_map(Context& context) const;
};

class ConceptNode : public ASTNode {
public:
    NameNode* key;
    StringNode* repr;

    ConceptNode(NameNode* key, StringNode* repr);
    ~ConceptNode() override;

    std::pair<std::string, std::shared_ptr<const dlplan::core::Concept>> get_concept(Context& context) const;
};

class ConceptListNode : public ASTNode {
public:
    std::vector<ConceptNode*> concept_nodes;

    ConceptListNode(const std::vector<ConceptNode*>& concept_nodes);
    ~ConceptListNode() override;
    ConceptMap get_concept_map(Context& context) const;
};

class ExtendedSketchNode : public ASTNode {
public:
    BooleanListNode* boolean_list_node;

    ExtendedSketchNode(BooleanListNode* boolean_list_node);
    ~ExtendedSketchNode() override;

    ExtendedSketch get_extended_sketch(Context& context) const;
};



}

#endif
