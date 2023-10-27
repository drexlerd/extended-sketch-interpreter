#include "symbol_table.hpp"


namespace sketches::extended_sketch {

SymbolTable::SymbolTable()
    : memory_states(MemoryStateFactory(*this)),
      registers(RegisterFactory(*this)),
      load_rules(LoadRuleFactory(*this)),
      call_rules(CallRuleFactory(*this)),
      action_rules(ActionRuleFactory(*this)),
      search_rules(SearchRuleFactory(*this)),
      extended_sketches(ExtendedSketchFactory(*this)) {}

}