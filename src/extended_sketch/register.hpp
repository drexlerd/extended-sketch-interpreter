#ifndef SRC_EXTENDED_SKETCH_REGISTER_HPP_
#define SRC_EXTENDED_SKETCH_REGISTER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include "declarations.hpp"
#include "symbol_factory.hpp"
#include "symbol_table.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;
struct Register;
using RegisterHandle = SymbolHandle<Register>;
using RegisterHandleList = std::vector<RegisterHandle>;


struct Register {
    SymbolTable& symbol_table;
    std::string name;
};


class RegisterFactory : public SymbolFactory<Register> {
};

}

#endif
