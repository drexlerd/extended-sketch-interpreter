#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_PARSER_HPP_

#include "ast.hpp"

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser {


/// @brief Parses the content from iter to end
extern ast::ExtendedSketch parse_ast(
    dlplan::common::parsers::iterator_type& iter,
    dlplan::common::parsers::iterator_type end,
    dlplan::common::parsers::error_handler_type& error_handler);

}

#endif
