#ifndef SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_HPP_
#define SRC_PRIVATE_PARSERS_SYNTACTIC_PARSER_HPP_

#include "ast.hpp"

#include "../../dlplan/include/dlplan/common/parsers/config.hpp"


namespace mimir::extended_sketch {
/// @brief Parses the content from iter to end
extern ast::ExtendedSketch parse_sketch_ast(
    dlplan::iterator_type& iter,
    dlplan::iterator_type end,
    dlplan::error_handler_type& error_handler);

/// @brief Parses the content from iter to end
extern ast::Module parse_module_ast(
    dlplan::iterator_type& iter,
    dlplan::iterator_type end,
    dlplan::error_handler_type& error_handler);

}

#endif
