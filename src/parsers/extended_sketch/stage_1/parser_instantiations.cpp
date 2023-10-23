#include "parser_def.hpp"

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"

using namespace dlplan::common::parsers;


namespace sketches::parsers::extended_sketch::stage_1::parser
{
    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_type, iterator_type, context_type)
}
