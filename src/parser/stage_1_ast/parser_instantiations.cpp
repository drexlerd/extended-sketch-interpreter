#include "parser_def.hpp"

#include "src/parser/common/config.hpp"


namespace sketches::extended_sketch::parser
{
    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_type, iterator_type, context_type)
}
