#ifndef SRC_PARSER_STAGE_2_AST_REGISTER_FACTORY_HPP_
#define SRC_PARSER_STAGE_2_AST_REGISTER_FACTORY_HPP_

#include <unordered_map>

#include "src/extended_sketch/declarations.hpp"


namespace sketches::extended_sketch {

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
