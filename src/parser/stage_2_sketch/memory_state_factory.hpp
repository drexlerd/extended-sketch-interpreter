#ifndef SRC_PARSER_STAGE_2_AST_MEMORY_STATE_FACTORY_HPP_
#define SRC_PARSER_STAGE_2_AST_MEMORY_STATE_FACTORY_HPP_

#include <unordered_map>

#include "src/extended_sketch/declarations.hpp"


namespace sketches::extended_sketch {

class MemoryStateFactory {
private:
    MemoryStateMap m_key_to_state;

public:
    MemoryState make_memory_state(const std::string& key);

    MemoryState get_memory_state(const std::string& key) const;
};

}


#endif
