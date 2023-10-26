#ifndef SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_
#define SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_

#include <string>
#include <memory>
#include <vector>

#include "declarations.hpp"
#include "symbol_factory.hpp"
#include "symbol_table.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;
struct MemoryState;
using MemoryStateHandle = SymbolHandle<MemoryState>;
using MemoryStateHandleList = std::vector<MemoryStateHandle>;


struct MemoryState {
    SymbolTable& symbol_table;
    std::string name;
};


class MemoryStateFactory : public SymbolFactory<MemoryState> {
};

}

#endif
