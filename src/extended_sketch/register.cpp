#include "register.hpp"


namespace sketches::extended_sketch {

Register::Register(SymbolTable& symbol_table, const std::string& name)
    : symbol_table(symbol_table), name(name) {
}

std::string Register::compute_signature() const {
    return name;
}

RegisterFactory::RegisterFactory(SymbolTable& symbol_table)
    : SymbolFactory<Register>(symbol_table) { }

}