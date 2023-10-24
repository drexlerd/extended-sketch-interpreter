#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_SYMBOL_TABLE_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_SYMBOL_TABLE_HPP_

#include <unordered_map>

#include "src/extended_sketch/declarations.hpp"

using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2 {

template<typename T>
class SymbolTable {
private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_key_to_symbol;

    void declare_symbol(const std::string& key) {
        m_key_to_symbol.insert(key, std::make_shared<T>(nullptr));
    }

    std::shared_ptr<T> get_symbol(const std::string& key) const {
        auto it = m_key_to_symbol.find(key);
        if (it == m_key_to_symbol.end()) {
            return nullptr;
        }
        return it->first;
    }
};


class SymbolTables {
private:
    SymbolTable<Register> registers;
    SymbolTable<MemoryState> memory_states;
    SymbolTable<Boolean> booleans;
    SymbolTable<Numerical> numericals;
    SymbolTable<Concept> concepts;
    SymbolTable<ExtendedSketch> extended_sketches;
};

}


#endif
