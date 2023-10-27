#ifndef SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_
#define SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_

#include <string>
#include <memory>
#include <vector>

#include "declarations.hpp"
#include "symbol_factory.hpp"


namespace sketches::extended_sketch {
class SymbolTable;
struct MemoryState;
using MemoryStateHandle = SymbolHandle<MemoryState>;
using MemoryStateHandleList = std::vector<MemoryStateHandle>;


struct MemoryState : public BaseSymbol {
    const SymbolTable* symbol_table;
    std::string name;

    MemoryState(const SymbolTable& symbol_table, const std::string& name);

    std::string compute_signature() const override;
};


class MemoryStateFactory : public SymbolFactory<MemoryState> {
public:
    MemoryStateFactory(const SymbolTable& symbol_table);
};

}

#endif
