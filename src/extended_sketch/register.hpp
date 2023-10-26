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


struct Register : public Symbol {
    SymbolTable& symbol_table;
    std::string name;

    Register(SymbolTable& symbol_table, const std::string& name);

    std::string compute_signature() const override;
};


class RegisterFactory : public SymbolFactory<Register> {
};

}

#endif
