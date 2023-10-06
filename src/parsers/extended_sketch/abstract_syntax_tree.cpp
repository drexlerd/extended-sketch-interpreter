#include "abstract_syntax_tree.hpp"

#include <sstream>

#include <boost/fusion/include/at_c.hpp>

#include "../../extended_sketch/extended_sketch.hpp"


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

/* QuotedStringNode */
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

/* ExtendedSketchNode */
BooleanNode::BooleanNode(NameNode* key, StringNode* repr)
    : key(key), repr(repr) { }

BooleanNode::~BooleanNode() = default;

std::pair<std::string, std::shared_ptr<const dlplan::core::Boolean>> BooleanNode::get_boolean(Context& context) const {
    return std::make_pair(key->get_name(), context.dlplan_element_factory->parse_boolean(repr->get_string()));
}

/* ExtendedSketchNode */
BooleanListNode::BooleanListNode(const std::vector<BooleanNode*>& boolean_nodes)
    : boolean_nodes(boolean_nodes) {}

BooleanListNode::~BooleanListNode() {
    for (auto node : boolean_nodes) {
        delete node;
    }
}

BooleanMap BooleanListNode::get_boolean_map(Context& context) const {
    BooleanMap result;
    for (const auto node : boolean_nodes) {
        result.insert(node->get_boolean(context));
    }
    return result;
}

ExtendedSketchNode::ExtendedSketchNode(BooleanListNode* boolean_list_node)
    : boolean_list_node(boolean_list_node) {}

ExtendedSketchNode::~ExtendedSketchNode() {
    delete boolean_list_node;
}

/* ExtendedSketchNode */
ExtendedSketch ExtendedSketchNode::get_extended_sketch(Context& context) const {
    BooleanList booleans;
    auto boolean_map = boolean_list_node->get_boolean_map(context);
    for (const auto& pair : boolean_map) {
        booleans.push_back(pair.second);
    }
    return ExtendedSketch(
        new ExtendedSketchImpl(
            MemoryStateList(),
            RegisterList(),
            std::move(booleans),
            NumericalList(),
            ConceptList(),
            MemoryState(),
            LoadRuleList(),
            CallRuleList(),
            ActionRuleList(),
            IWSearchRuleList()));
}

}
