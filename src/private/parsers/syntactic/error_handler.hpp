#ifndef SRC_PRIVATE_PARSERS_SYNTACTIC_ERROR_HANDLER_HPP_
#define SRC_PRIVATE_PARSERS_SYNTACTIC_ERROR_HANDLER_HPP_

#include <map>
#include <iostream>

#include "../../dlplan/include/dlplan/policy/parsers/syntactic/error_handler.hpp"


namespace mimir::extended_sketch
{
    namespace x3 = boost::spirit::x3;

    struct error_handler_extended_sketch : dlplan::policy::error_handler_policy {
        error_handler_extended_sketch() : dlplan::policy::error_handler_policy() {
            id_map[""] = "";
        }
    };

    struct error_handler_extended_module : error_handler_extended_sketch {
        error_handler_extended_module() : error_handler_extended_sketch() {
            id_map[""] = "";
        }
    };
}

#endif
