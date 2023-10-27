#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_HPP_

#include <memory>
#include <vector>

#include "declarations.hpp"
#include "arguments.hpp"
#include "signature.hpp"
#include "register.hpp"
#include "memory_state.hpp"
#include "rules.hpp"
#include "symbol_factory.hpp"


namespace sketches::extended_sketch {
class SymbolTable;
class ExtendedSketch;
using ExtendedSketchHandle = SymbolHandle<ExtendedSketch>;
using ExtendedSketchFactory = SymbolFactory<ExtendedSketch>;

class ExtendedSketch {
private:
    // We can get access to other sketches here
    const SymbolTable* m_parent_symbol_table;

    std::unique_ptr<SymbolTable> m_symbol_table;

    Signature m_signature;

    MemoryStateHandleList m_memory_states;
    MemoryStateHandle m_initial_memory_state;

    RegisterHandleList m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    LoadRuleHandleList m_load_rules;
    CallRuleHandleList m_call_rules;
    ActionRuleHandleList m_action_rules;
    SearchRuleHandleList m_iwsearch_rules;

public:
    ExtendedSketch(
        const SymbolTable& parent_symbol_table,
        std::unique_ptr<SymbolTable>&& symbol_table,
        const Signature& signature,
        const MemoryStateHandleList& memory_states,
        const MemoryStateHandle& initial_memory_state,
        const RegisterHandleList& registers,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const LoadRuleHandleList& load_rules,
        const CallRuleHandleList& call_rules,
        const ActionRuleHandleList& action_rules,
        const SearchRuleHandleList& iwsearch_rules);

    std::string compute_signature() const;
};

}

#endif
