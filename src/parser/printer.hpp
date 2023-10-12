#ifndef SRC_PARSER_PRINTER_HPP_
#define SRC_PARSER_PRINTER_HPP_


#include "ast.hpp"

#include <ostream>

namespace rexpr { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  Print out the rexpr tree
    ///////////////////////////////////////////////////////////////////////////
    int const tabsize = 4;

    struct rexpr_printer
    {
        typedef void result_type;

        rexpr_printer(std::ostream& out, int indent = 0)
          : out(out), indent(indent) {}

        void operator()(rexpr const& ast) const
        {
            out << '{' << std::endl;
            for (auto const& entry : ast.entries)
            {
                tab(indent+tabsize);
                out << '"' << entry.first << "\" = ";
                boost::apply_visitor(rexpr_printer(out, indent+tabsize), entry.second);
            }
            tab(indent);
            out << '}' << std::endl;
        }

        void operator()(std::string const& text) const
        {
            out << '"' << text << '"' << std::endl;
        }

        void tab(int spaces) const
        {
            for (int i = 0; i < spaces; ++i)
                out << ' ';
        }

        std::ostream& out;
        int indent;
    };
}}

#endif
