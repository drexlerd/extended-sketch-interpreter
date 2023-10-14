#include "parser_def.hpp"

#include "src/parsers/common/config.hpp"


namespace sketches::parsers::extended_sketch::stage_1::parser
{
    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_type, iterator_type, context_type)
}
