#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_REGISTER_FACTORY_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_REGISTER_FACTORY_HPP_

#include <unordered_map>

#include "src/extended_sketch/declarations.hpp"

using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2 {

/// @brief Provides functionality
class RegisterFactory {
private:
    RegisterMap m_key_to_state;

public:
    Register make_register(const std::string& key);

    Register get_register(const std::string& key) const;
};

}


#endif
