#ifndef SRC_EXTENDED_SKETCH_RULES_HPP_
#define SRC_EXTENDED_SKETCH_RULES_HPP_

#include "declarations.hpp"


namespace sketches::extended_sketch {
class ExtendedRuleImpl {
protected:
    MemoryState m_body_memory_state;
    MemoryState m_head_memory_state;

public:
    ExtendedRuleImpl(
        const MemoryState& body_memory_state,
        const MemoryState& head_memory_state);
    virtual ~ExtendedRuleImpl();

    virtual const MemoryState& get_body_memory_state() const;
    virtual const MemoryState& get_head_memory_state() const;
};

class LoadRuleImpl {
public:
};

class CallRuleImpl {
public:
};

class ActionRuleImpl {
public:
};

class IWSearchRuleImpl {
public:
};
}

#endif
