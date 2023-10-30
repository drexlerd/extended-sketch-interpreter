#ifndef SRC_PARSERS_MODULE_STAGE_1_PARSER_API_HPP_
#define SRC_PARSERS_MODULE_STAGE_1_PARSER_API_HPP_

#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"


namespace sketches::parsers::module::stage_1
{
    namespace x3 = boost::spirit::x3;

    ///////////////////////////////////////////////////////////////////////////
    // rexpr public interface
    ///////////////////////////////////////////////////////////////////////////
    namespace parser {
        struct ModuleClass;
        struct ModuleRootClass;

        typedef x3::rule<ModuleClass, ast::Module> module_type;
        typedef x3::rule<ModuleRootClass, ast::Module> module_root_type;


        BOOST_SPIRIT_DECLARE(
            module_type, module_root_type
        )
    }

    parser::module_type const& module_();
    parser::module_root_type const& module_root();
}

#endif