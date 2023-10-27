#ifndef SRC_EXTENDED_SKETCH_SCOPE_HPP_
#define SRC_EXTENDED_SKETCH_SCOPE_HPP_

#include <vector>

#include "src/extended_sketch/symbol_table.hpp"


namespace sketches::parsers {
struct Scope;

/// @brief The outtermost scope is also called the global scope.
struct Scope {
    std::unique_ptr<sketches::extended_sketch::SymbolTable> symbol_table;

    std::vector<Scope> child_scopes;
};

}


#endif