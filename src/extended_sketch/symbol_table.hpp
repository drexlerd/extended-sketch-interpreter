#ifndef SRC_EXTENDED_SKETCH_SYMBOL_TABLE_HPP_
#define SRC_EXTENDED_SKETCH_SYMBOL_TABLE_HPP_

#include "extended_sketch.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "rules.hpp"


namespace sketches::extended_sketch {
/// @brief All symbols are registered here in a flat manner to avoid circular dependencies.
///        References are represented with handle types.
///        Factories are used for controlled creation of objects and to retrieve handles to existing objects.
///        A SymbolTable must be allocated on the heap for pointers to not become invalid.
struct SymbolTable {
    MemoryStateFactory memory_states;
    RegisterFactory registers;
    LoadRuleFactory load_rules;
    CallRuleFactory call_rules;
    ActionRuleFactory action_rules;
    SearchRuleFactory search_rules;
    ExtendedSketchFactory extended_sketches;

    SymbolTable();
};

SymbolTable::SymbolTable()
    : memory_states(MemoryStateFactory(*this)),
      registers(RegisterFactory(*this)),
      load_rules(LoadRuleFactory(*this)),
      call_rules(CallRuleFactory(*this)),
      action_rules(ActionRuleFactory(*this)),
      search_rules(SearchRuleFactory(*this)),
      extended_sketches(ExtendedSketchFactory(*this)) {}



}

#endif
