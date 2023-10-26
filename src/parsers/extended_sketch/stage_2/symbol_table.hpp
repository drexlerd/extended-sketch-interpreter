#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_SYMBOL_TABLE_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_SYMBOL_TABLE_HPP_

#include <unordered_map>

#include "src/parsers/extended_sketch/stage_1/ast.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy/parsers/policy/stage_1/ast.hpp"

#include "src/extended_sketch/declarations.hpp"
#include "../../../extended_sketch/register.hpp"

using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2 {

template<typename N, typename T>
struct Symbol {
    // Node in ast that declared this symbol.
    // We can use it to print error messages that refer to the declaration.
    const N& node;
    // We use a nested pointer to perform lazy initialization of T.
    const std::shared_ptr<std::unique_ptr<T>> value;

    Symbol(const N& node_)
        : node(node_),
          value(std::make_shared<std::unique_ptr<T>>(nullptr)) { }

    bool is_defined() const {
        return static_cast<bool>(*value);
    }

    T& define(T&& value_) {
        return *(*value = std::make_unique<T>(std::move(value_)));
    }

    T& get_definition() {
        assert(is_defined());
        return **value;
    }
};

template<typename N, typename T>
class SymbolTable {
private:
    std::unordered_map<std::string, Symbol<N, T>> m_symbols;

public:
    Symbol<N, T>& add_symbol(const std::string& signature, const N& node) {
        return m_symbols.emplace(signature, Symbol<N, T>(node)).first->second;
    }

    bool exists_symbol(const std::string& signature) const {
        return m_symbols.count(signature);
    }

    Symbol<N, T>& get_symbol(const std::string& signature) {
        assert(exists_symbol(signature));
        return m_symbols.at(signature);
    }
};

struct SymbolTables {
    SymbolTable<sketches::parsers::extended_sketch::stage_1::ast::Register, Register> registers;
    SymbolTable<sketches::parsers::extended_sketch::stage_1::ast::MemoryState, MemoryState> memory_states;
    SymbolTable<sketches::parsers::extended_sketch::stage_1::ast::ExtendedSketch, ExtendedSketch> extended_sketches;
};

}


#endif
