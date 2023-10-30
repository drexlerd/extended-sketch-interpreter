#include "symbol_table.hpp"


namespace sketches::extended_sketch {

SymbolTable::SymbolTable()
    : memory_states(Factory<MemoryState>(*this)),
      registers(Factory<Register>(*this)),
      load_rules(Factory<LoadRule>(*this)),
      call_rules(Factory<CallRule>(*this)),
      action_rules(Factory<ActionRule>(*this)),
      search_rules(Factory<SearchRule>(*this)),
      extended_sketches(Factory<ExtendedSketch>(*this)) {}

}