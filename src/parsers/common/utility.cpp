#include "utility.hpp"


namespace sketches::parsers {

bool in_bounds(
    const std::string& source,
    const iterator_type& iter, const iterator_type& end) {
    if ((source.begin() > iter && source.begin() < end) ||
        (source.end() > iter && source.end() < end)) {
        return false;
    }
    return true;
}

}