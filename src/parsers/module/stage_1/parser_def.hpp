#ifndef SRC_PARSERS_MODULE_STAGE_1_PARSER_DEF_HPP_
#define SRC_PARSERS_MODULE_STAGE_1_PARSER_DEF_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "ast_adapted.hpp"
#include "ast.hpp"
#include "error_handler.hpp"
#include "parser_api.hpp"

#include "src/parsers/extended_sketch/stage_1/parser_api.hpp"



namespace sketches::parsers::module::stage_1 { namespace parser
{
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;

    using x3::lit;
    using x3::lexeme;

    using ascii::alpha;
    using ascii::alnum;
    using ascii::char_;
    using ascii::string;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct SignatureClass;


    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    x3::rule<SignatureClass, ast::Signature> const
        signature = "signature";

    module_type const module_ = "module";

    module_root_type const module_root = "module";


    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    const auto signature_def = lit('(') >> lit(":signature")
        > sketches::parsers::extended_sketch::stage_1::name()
            > lit('(')
                >> sketches::parsers::extended_sketch::stage_1::argument() % lit(',')
            > lit(')')
        > lit(')');

    const auto module__def = lit('(') >> lit(":module")
        > signature
        > sketches::parsers::extended_sketch::stage_1::extended_sketch()
        > lit(')');
    const auto module_root_def = module_;

    BOOST_SPIRIT_DEFINE(signature, module_, module_root)

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct SignatureClass : x3::annotate_on_success {};

    struct ModuleClass : x3::annotate_on_success {};
    struct ModuleRootClass : x3::annotate_on_success, error_handler_extended_module {};
}}

namespace sketches::parsers::module::stage_1
{
    parser::module_type const& module_() {
        return parser::module_;
    }

    parser::module_root_type const& module_root() {
        return parser::module_root;
    }
}

#endif