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
#include "context.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <string>


namespace sketches::extended_sketch::parser {
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace fusion = boost::fusion;

struct ExtendedSketchGrammar : public qi::grammar<std::string::iterator, ExtendedSketchNode*(), ascii::space_type> {
    // list of rules, the middle argument to the template is the return value of the grammar
    qi::rule<std::string::iterator, char()> ANY_CHAR;
    qi::rule<std::string::iterator, NameNode(), ascii::space_type> NAME;
    qi::rule<std::string::iterator, char()> STRING_CHAR;
    qi::rule<std::string::iterator, StringNode(), ascii::space_type> STRING;
    qi::rule<std::string::iterator, IdentifierNode(), ascii::space_type> IDENTIFIER;
    qi::rule<std::string::iterator, NameAndStringNode(), ascii::space_type> NAME_AND_STRING;
    qi::rule<std::string::iterator, LoadRuleNode*(), ascii::space_type> LOAD_RULE;
    qi::rule<std::string::iterator, CallRuleNode*(), ascii::space_type> CALL_RULE;
    qi::rule<std::string::iterator, ActionRuleNode*(), ascii::space_type> ACTION_RULE;
    qi::rule<std::string::iterator, IWSearchRuleNode*(), ascii::space_type> IWSEARCH_RULE;
    qi::rule<std::string::iterator, LoadCallActionOrIWSearchRuleNode*(), ascii::space_type> LOAD_CALL_ACTION_OR_IWSEARCH_RULE;
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
        using qi::_8;
        using qi::_val;
        using spirit::double_;
        using spirit::int_;
        using spirit::lit;

        // Names
        ANY_CHAR = alpha           // alphabetical character
                    | alnum        // alphanumerical character
                    | char_('-')   // dash character
                    | char_('_');  // underscore character

        NAME = (alpha >> *ANY_CHAR)[_val = construct<NameNode>(_1, _2)];  // a name must start with an alphabetical character

        // Identifier nodes (start with colon)
        IDENTIFIER = (lit(':') > +ANY_CHAR)[_val = construct<IdentifierNode>(_1)];

        // String characters (used for dlplan features)
        STRING_CHAR = alpha        // alphabetical character
                    | alnum        // alphanumerical character
                    | char_('-')   // dash character
                    | char_('_')   // underscore character
                    | char_('(')   // opening parentheses character
                    | char_(')')   // closing parentheses character
                    | char_(',');  // comma character

        STRING = (lit('"') > +STRING_CHAR > lit('"'))[_val = construct<StringNode>(_1)];

        // Name and string
        NAME_AND_STRING = (lit('(') > NAME > STRING > lit(')'))[_val = construct<NameAndStringNode>(_1, _2)];

        //// Rules
        //// (:rule (:conditions (:memory )) (:effects (:memory )))
        //IWSEARCH_RULE = (
        //    lit('(')
        //    > lit(":rule")
        //        > lit('(')
        //        > lit(":conditions")
        //            > (lit('(') > lit(":memory") > NAME > lit(')'))  // memory
        //        > lit(')')  // conditions
        //        > lit('(')
        //        > lit(":effects")
        //            > lit('(') > lit(":memory") > NAME > lit(')')  // memory
        //        > lit(')')  // effects
        //    > lit(')'))[_val = new_<IWSearchRuleNode>(_1, _2, std::vector<FeatureConditionNode*>{}, std::vector<FeatureEffectNode*>{})];
//
        //LOAD_CALL_ACTION_OR_IWSEARCH_RULE = IWSEARCH_RULE[_val = new_<LoadCallActionOrIWSearchRuleNode>(_1)];
//
        ////// Domain
        //EXTENDED_SKETCH_DESCRIPTION = (lit('(') > lit(":extended_sketch")
        //                          > lit('(') > lit(":name") > NAME > lit(')')
        //                          > lit('(') > lit(":memory_states") > lit('(') > *NAME > lit(')') > lit(')')
        //                          > lit('(') > lit(":initial_memory_state") > NAME > lit(')')
        //                          > lit('(') > lit(":registers") > lit('(') > *NAME > lit(')') > lit(')')
        //                          > lit('(') > lit(":booleans") > *NAME_AND_STRING > lit(')')
        //                          > lit('(') > lit(":numericals") > *NAME_AND_STRING > lit(')')
        //                          > lit('(') > lit(":concepts") > *NAME_AND_STRING > lit(')')
        //                          >> *LOAD_CALL_ACTION_OR_IWSEARCH_RULE
        //                          > lit(')'))[_val = construct<ExtendedSketchNode>(_1, _2, _3, _4, _5, _6, _7, _8)];
    }
};

ExtendedSketchParser::ExtendedSketchParser(const fs::path& sketch_path)
    : m_sketch_path(sketch_path) { }

ExtendedSketch ExtendedSketchParser::parse(
    const mimir::formalism::DomainDescription& domain_description,
    std::shared_ptr<dlplan::core::SyntacticElementFactory> factory,
    std::shared_ptr<dlplan::policy::PolicyBuilder> builder) {
    Context context(domain_description, factory, builder);
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

            bool parse_success = qi::phrase_parse(iterator_begin, iterator_end, extended_sketch_grammar, ascii::space, sketch_node);
            if (parse_success)
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
