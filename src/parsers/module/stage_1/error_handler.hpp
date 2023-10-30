#ifndef SRC_PARSERS_MODULE_STAGE_1_ERROR_HANDLER_HPP_
#define SRC_PARSERS_MODULE_STAGE_1_ERROR_HANDLER_HPP_

#include <map>
#include <iostream>

#include "src/parsers/extended_sketch/stage_1/error_handler.hpp"


namespace sketches::parsers::module::stage_1
{
    namespace x3 = boost::spirit::x3;

    struct error_handler_extended_module : sketches::parsers::extended_sketch::stage_1::error_handler_extended_sketch {
        error_handler_extended_module() : sketches::parsers::extended_sketch::stage_1::error_handler_extended_sketch() {
            id_map[""] = "";
        }
    };
}

#endif
