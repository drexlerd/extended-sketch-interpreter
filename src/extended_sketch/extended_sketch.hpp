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


class ExtendedSketch {
private:
    // Data underlying handles.
    SymbolTable const* m_parent_symbol_table;
    std::unique_ptr<const SymbolTable> m_symbol_table;

    Signature m_signature;

    std::vector<Handle<MemoryState>> m_memory_states;
    Handle<MemoryState> m_initial_memory_state;

    std::vector<Handle<Register>> m_registers;

    BooleanMap m_booleans;
    NumericalMap m_numericals;
    ConceptMap m_concepts;

    std::vector<Handle<LoadRule>> m_load_rules;
    std::vector<Handle<CallRule>> m_call_rules;
    std::vector<Handle<ActionRule>> m_action_rules;
    std::vector<Handle<SearchRule>> m_iwsearch_rules;

public:
    ExtendedSketch(
        const SymbolTable& parent_symbol_table,
        std::unique_ptr<const SymbolTable>&& symbol_table,
        const Signature& signature,
        const std::vector<Handle<MemoryState>>& memory_states,
        const Handle<MemoryState>& initial_memory_state,
        const std::vector<Handle<Register>>& registers,
        const BooleanMap& booleans,
        const NumericalMap& numericals,
        const ConceptMap& concepts,
        const std::vector<Handle<LoadRule>>& load_rules,
        const std::vector<Handle<CallRule>>& call_rules,
        const std::vector<Handle<ActionRule>>& action_rules,
        const std::vector<Handle<SearchRule>>& iwsearch_rules);

    std::string compute_signature() const;
};

}

#endif
