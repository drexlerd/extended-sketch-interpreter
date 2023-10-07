#include "../../include/dlplan/core.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


namespace dlplan::core {

Register::Register() : m_index(-1) { }

Register::Register(RegisterIndex index) : m_index(index) { }

RegisterIndex Register::get_index() const {
    return m_index;
}

}


namespace boost::serialization {
template<typename Archive>
void serialize( Archive& ar, dlplan::core::Register& t, const unsigned int /* version */ )
{
    ar & t.m_index;
}

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::core::Register& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::core::Register& t, const unsigned int version);
}
