/*
 * Copyright (C) 2023 Simon Stahlberg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "extended_sketch_parser.hpp"

#include "abstract_syntax_tree.hpp"
#include "parser_includes.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


namespace sketches::extended_sketch::parser {
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace fusion = boost::fusion;

struct ExtendedSketchGrammar : public qi::grammar<std::string::iterator, ExtendedSketchNode*(), ascii::space_type> {
    // list of rules, the middle argument to the template is the return value of the grammar
    qi::rule<std::string::iterator, CharacterNode*()> ANY_CHAR;
    qi::rule<std::string::iterator, NameNode*()> NAME;
    qi::rule<std::string::iterator, StringNode*(), ascii::space_type> STRING;
    qi::rule<std::string::iterator, BooleanNode*(), ascii::space_type> BOOLEAN;
    qi::rule<std::string::iterator, BooleanListNode*(), ascii::space_type> BOOLEAN_LIST;
    qi::rule<std::string::iterator, NumericalNode*(), ascii::space_type> NUMERICAL;
    qi::rule<std::string::iterator, NumericalListNode*(), ascii::space_type> NUMERICAL_LIST;
    qi::rule<std::string::iterator, ConceptNode*(), ascii::space_type> CONCEPT;
    qi::rule<std::string::iterator, ConceptListNode*(), ascii::space_type> CONCEPT_LIST;
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

        // Names
        ANY_CHAR = alpha[_val = new_<CharacterNode>(_1)]           // alphabetical character
                    | alnum[_val = new_<CharacterNode>(_1)]        // alphanumerical character
                    | char_('-')[_val = new_<CharacterNode>(_1)]   // dash character
                    | char_('_')[_val = new_<CharacterNode>(_1)]   // underscore character
                    | char_('(')[_val = new_<CharacterNode>(_1)]   // opening parentheses character
                    | char_(')')[_val = new_<CharacterNode>(_1)]   // closing parentheses character
                    | char_(',')[_val = new_<CharacterNode>(_1)];  // comma character

        NAME = (alpha >> *ANY_CHAR)[_val = new_<NameNode>(_1, _2)];  // a name must start with an alphabetical character

        STRING = (lit('"') > +ANY_CHAR > lit('"'))[_val = new_<StringNode>(_1)];

        // Booleans
        BOOLEAN = (lit('(') > NAME > STRING > lit(')'))[_val = new_<BooleanNode>(_1, _2)];

        BOOLEAN_LIST = (lit('(') > lit(":booleans") > *BOOLEAN > lit(')'))[_val = new_<BooleanListNode>(_1)];

        // Numericals
        NUMERICAL = (lit('(') > NAME > STRING > lit(')'))[_val = new_<NumericalNode>(_1, _2)];

        NUMERICAL_LIST = (lit('(') > lit(":numericals") > *NUMERICAL > lit(')'))[_val = new_<NumericalListNode>(_1)];

        // Concepts
        CONCEPT = (lit('(') > NAME > STRING > lit(')'))[_val = new_<ConceptNode>(_1, _2)];

        CONCEPT_LIST = (lit('(') > lit(":concepts") > *CONCEPT > lit(')'))[_val = new_<ConceptListNode>(_1)];

        // Domain
        EXTENDED_SKETCH_DESCRIPTION = (lit('(') > lit(":extended_sketch")
                                  > BOOLEAN_LIST
                                  > NUMERICAL_LIST
                                  > CONCEPT_LIST
                                  > lit(')'))[_val = new_<ExtendedSketchNode>(_1)];
    }
};

ExtendedSketchParser::ExtendedSketchParser(const fs::path& sketch_path)
    : m_sketch_path(sketch_path) { }

ExtendedSketch ExtendedSketchParser::parse(Context& context) {
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
                    const auto extended_sketch = sketch_node->get_extended_sketch(context);
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
