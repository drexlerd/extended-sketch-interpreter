#ifndef SRC_EXTENDED_SKETCH_REGISTER_HPP_
#define SRC_EXTENDED_SKETCH_REGISTER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include "declarations.hpp"
#include "symbol_factory.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;
struct Register;
using RegisterHandle = SymbolHandle<Register>;
using RegisterHandleList = std::vector<RegisterHandle>;
using RegisterFactory = SymbolFactory<Register>;


struct Register {
    SymbolTable const* symbol_table;
    std::string name;

    Register(const SymbolTable& symbol_table, const std::string& name);

    std::string compute_signature() const;
};

}

#endif
