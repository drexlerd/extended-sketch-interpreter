#ifndef SRC_EXTENDED_SKETCH_PARSER_ABSTRACT_SYNTAX_TREE_HPP_
#define SRC_EXTENDED_SKETCH_PARSER_ABSTRACT_SYNTAX_TREE_HPP_

#include "../declarations.hpp"

namespace sketches::extended_sketch::parser {
class ASTNode {
public:
    virtual ~ASTNode();
};

class ExtendedSketchNode : public ASTNode {
public:
    ExtendedSketch get_extended_sketch() const;
};
}

#endif
