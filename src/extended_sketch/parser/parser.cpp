#include "parser.hpp"

#include <fstream>

#include "parser_includes.hpp"

#include "abstract_syntax_tree.hpp"

namespace sketches::extended_sketch::parser {
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace fusion = boost::fusion;

struct ExtendedSketchGrammar : public qi::grammar<std::string::iterator, ExtendedSketchNode*(), ascii::space_type> {
    // list of rules, the middle argument to the template is the return value of the grammar
    qi::rule<std::string::iterator, ExtendedSketchNode*(), ascii::space_type> EXTENDED_SKETCH_DESCRIPTION;

    ExtendedSketchGrammar() : ExtendedSketchGrammar::base_type(EXTENDED_SKETCH_DESCRIPTION) {
        // include the following to make the grammar below more readable
        using ascii::alnum;
        using ascii::alpha;
        using ascii::char_;
        using ascii::string;
        using phoenix::at_c;
        using phoenix::construct;
        using phoenix::new_;
        using phoenix::val;
        using qi::_1;
        using qi::_2;
        using qi::_3;
        using qi::_4;
        using qi::_5;
        using qi::_6;
        using qi::_7;
        using qi::_val;
        using spirit::double_;
        using spirit::int_;
        using spirit::lit;

        // Domain
        EXTENDED_SKETCH_DESCRIPTION = (string("(") > string(":sketch")
                                  > string(")"))[_val = new_<ExtendedSketchNode>()];
    }
};

ExtendedSketchParser::ExtendedSketchParser(const fs::path& sketch_path)
    : m_sketch_path(sketch_path) { }

ExtendedSketch ExtendedSketchParser::parse() {
    if (fs::exists(m_sketch_path)) {
        std::ifstream sketch_stream(this->m_sketch_path.c_str());
        if (sketch_stream.is_open()) {
            std::stringstream buffer;
            buffer << sketch_stream.rdbuf();
            std::string sketch_content = buffer.str();

            ExtendedSketchGrammar extended_sketch_grammar;
            auto iterator_begin = sketch_content.begin();
            auto iterator_end = sketch_content.end();
            ExtendedSketchNode* sketch_node = nullptr;

            if (qi::phrase_parse(iterator_begin, iterator_end, extended_sketch_grammar, ascii::space, sketch_node))
                {
                    const auto extended_sketch = sketch_node->get_extended_sketch();
                    delete sketch_node;
                    return extended_sketch;
                }
                else
                {
                    if (sketch_node)
                    {
                        delete sketch_node;
                    }

                    throw std::runtime_error("extended sketch could not be parsed");
                }
        }
    }
    throw std::invalid_argument("extended sketch file does not exist");
}
}
