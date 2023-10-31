#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_ERROR_HANDLER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_1_ERROR_HANDLER_HPP_

#include <map>
#include <iostream>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/syntactic/error_handler.hpp"


namespace sketches::parsers::extended_sketch::stage_1
{
    namespace x3 = boost::spirit::x3;

    struct error_handler_extended_sketch : dlplan::policy::error_handler_policy {
        error_handler_extended_sketch() : dlplan::policy::error_handler_policy() {
            id_map[""] = "";
        }
    };
}

#endif
