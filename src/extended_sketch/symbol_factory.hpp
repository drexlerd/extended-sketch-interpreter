#ifndef SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_
#define SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <iostream>

#include "symbol_handle.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;


/// @brief Factory for the controlled creation and access of symbols.
template<typename Symbol>
class Factory {
protected:
    const SymbolTable* symbol_table;
    std::unordered_map<std::string, int> signature_to_handle;
    std::vector<Symbol> symbols;

public:
    explicit Factory(const SymbolTable& symbol_table_) : symbol_table(&symbol_table_) {
    }

    template<class... Args>
    Handle<Symbol> register_symbol(Args... args) {
        Symbol symbol(*symbol_table, std::forward<Args>(args)...);
        std::string signature = symbol.compute_signature();
        const auto& it = signature_to_handle.find(signature);
        if (it != signature_to_handle.end()) {
            return Handle<Symbol>{it->second};
        }
        int index = symbols.size();
        signature_to_handle.emplace(signature, index);
        symbols.push_back(std::move(symbol));
        return Handle<Symbol>{index};
    }

    template<class... Args>
    Handle<Symbol> get_handle(Args... args) const {
        Symbol symbol(*symbol_table, std::forward<Args>(args)...);
        std::string signature = symbol.compute_signature();
        if (signature_to_handle.count(signature)) {
            return signature_to_handle.at(signature);
        }
        return Handle<Symbol>::undefined;
    }

    Symbol& get_symbol(Handle<Symbol> handle) {
        assert(handle != Handle<Symbol>::undefined);
        return symbols[handle.index];
    }

    const Symbol& get_symbol(Handle<Symbol> handle) const {
        assert(handle != Handle<Symbol>::undefined);
        return symbols[handle.index];
    }

    Symbol& operator[](Handle<Symbol> handle) {
        return get_symbol(handle);
    }

    const Symbol& operator[](Handle<Symbol> handle) const {
        return get_symbol(handle);
    }
};


}

#endif
