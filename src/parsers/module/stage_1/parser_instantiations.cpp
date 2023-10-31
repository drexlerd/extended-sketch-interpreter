#include "parser_def.hpp"

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"

using namespace dlplan;


namespace sketches::parsers::module::stage_1::parser
{
    BOOST_SPIRIT_INSTANTIATE(
        module_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        module_root_type, iterator_type, context_type)
}
