#include "rexpr_def.hpp"
#include "config.hpp"


namespace sketches::extended_sketch { namespace parser
{
    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_type, iterator_type, context_type)
}}
