#ifndef SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_
#define SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>


namespace sketches::extended_sketch {
struct SymbolTable;
template<typename Symbol>
class SymbolFactory;

/// @brief Interface for symbols.
///        Each symbol must provide a way to construct a unique signature.
struct BaseSymbol {
    virtual ~BaseSymbol() = default;
    virtual std::string compute_signature() const = 0;
};


/// @brief Lightweight reference to the Symbol.
///        This allows fast reference from one place in the ast to another
template<typename Symbol>
class SymbolHandle {
private:
    int index;

    SymbolHandle(int index_) : index(index_) { }

    friend class SymbolFactory<Symbol>;

public:
    bool operator==(const SymbolHandle& other) const {
        return index == other.index;
    }

    bool operator!=(const SymbolHandle& other) const {
        return !(*this == other);
    }

    static SymbolHandle undefined;
};

template<typename Symbol>
SymbolHandle<Symbol> SymbolHandle<Symbol>::undefined = SymbolHandle<Symbol>(-1);


/// @brief Factory for the controlled creation and access of symbols.
template<typename Symbol>
class SymbolFactory {
protected:
    SymbolTable& symbol_table;
    std::unordered_map<std::string, int> signature_to_handle;
    std::vector<Symbol> symbols;

public:
    explicit SymbolFactory(SymbolTable& symbol_table_) : symbol_table(symbol_table_) { }

    template<class... Args>
    SymbolHandle<Symbol> register_symbol(Args... args) {
        Symbol symbol(symbol_table, args...);
        std::string signature = symbol.compute_signature();
        const auto& it = signature_to_handle.find(signature);
        if (it != signature_to_handle.end()) {
            return SymbolHandle<Symbol>{it->second};
        }
        int index = data.size();
        signature_to_handle.emplace(signature, index);
        symbols.push_back(symbol);
        return SymbolHandle<Symbol>{index};
    }

    template<class... Args>
    SymbolHandle<Symbol> get_handle(Args... args) const {
        Symbol symbol(symbol_table, args...);
        std::string signature = symbol.compute_signature();
        assert(signature_to_handle.count(signature));
        return signature_to_handle.at(signature);
    }

    Symbol& get_symbol(SymbolHandle<Symbol> handle) {
        assert(handle != SymbolHandle<Symbol>::undefined);
        return symbols[handle.index];
    }

    const Symbol& get_symbol(SymbolHandle<Symbol> handle) const {
        assert(handle != SymbolHandle<Symbol>::undefined);
        return symbols[handle.index];
    }

    Symbol& operator[](SymbolHandle<Symbol> handle) {
        return get_symbol(handle);
    }

    const Symbol& operator[](SymbolHandle<Symbol> handle) const {
        return get_symbol(handle);
    }
};


}

#endif
