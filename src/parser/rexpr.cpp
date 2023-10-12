#include "rexpr_def.hpp"
#include "config.hpp"

namespace rexpr { namespace parser
{
    BOOST_SPIRIT_INSTANTIATE(
        rexpr_type, iterator_type, context_type)
}}
