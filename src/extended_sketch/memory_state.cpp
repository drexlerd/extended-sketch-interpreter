#include "memory_state.hpp"


namespace sketches::extended_sketch {

MemoryState::MemoryState(SymbolTable& symbol_table, const std::string& name)
    : symbol_table(symbol_table), name(name) {
}

std::string MemoryState::compute_signature() const {
    return name;
}

MemoryStateFactory::MemoryStateFactory(SymbolTable& symbol_table)
    : SymbolFactory<MemoryState>(symbol_table) { }

}