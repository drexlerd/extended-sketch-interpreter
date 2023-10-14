#ifndef SRC_PARSERS_COMMON_UTILITY_HPP_
#define SRC_PARSERS_COMMON_UTILITY_HPP_

#include <map>

#include "config.hpp"


namespace sketches::parsers
{
extern bool in_bounds(
    const std::string& source,
    const iterator_type& iter, const iterator_type& end);
}

#endif
