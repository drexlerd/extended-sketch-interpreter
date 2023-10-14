#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_MEMORY_STATE_FACTORY_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_MEMORY_STATE_FACTORY_HPP_

#include <unordered_map>

#include "src/extended_sketch/declarations.hpp"

using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2 {

class MemoryStateFactory {
private:
    MemoryStateMap m_key_to_state;

public:
    MemoryState make_memory_state(const std::string& key);

    MemoryState get_memory_state(const std::string& key) const;
};

}


#endif
