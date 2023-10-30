#ifndef SRC_MODULE_CALL_TABLE_HPP_
#define SRC_MODULE_CALL_TABLE_HPP_

#include "module.hpp"


namespace sketches::extended_sketch {

struct SymbolTable {
    Factory<Module> modules;

    SymbolTable();
};

}

#endif
