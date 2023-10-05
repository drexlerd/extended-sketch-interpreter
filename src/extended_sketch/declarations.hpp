#ifndef SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_
#define SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_

#include <memory>
#include <vector>

#include "memory_state.hpp"

namespace sketches::extended_sketch {
    class MemoryStateImpl;
    using MemoryState = std::shared_ptr<MemoryStateImpl>;
    using MemoryStateList = std::vector<MemoryState>;

    class RegisterImpl;
    using Register = std::shared_ptr<RegisterImpl>;
    using RegisterList = std::vector<Register>;

    class BooleanImpl;
    using Boolean = std::shared_ptr<BooleanImpl>;
    using BooleanList = std::vector<Boolean>;

    class NumericalImpl;
    using Numerical = std::shared_ptr<NumericalImpl>;
    using NumericalList = std::vector<Numerical>;

    class ConceptImpl;
    using Concept = std::shared_ptr<ConceptImpl>;
    using ConceptList = std::vector<Concept>;

    class LoadRuleImpl;
    using LoadRule = std::shared_ptr<LoadRuleImpl>;
    using LoadRuleList = std::vector<LoadRule>;

    class CallRuleImpl;
    using CallRule = std::shared_ptr<CallRuleImpl>;
    using CallRuleList = std::vector<CallRule>;

    class ActionRuleImpl;
    using ActionRule = std::shared_ptr<ActionRuleImpl>;
    using ActionRuleList = std::vector<ActionRule>;

    class ExtendedStateImpl;
    using ExtendedState = std::shared_ptr<ExtendedStateImpl>;
    using ExtendedStateList = std::vector<ExtendedState>;

    class IWSearchRuleImpl;
    using IWSearchRule = std::shared_ptr<IWSearchRuleImpl>;
    using IWSearchRuleList = std::vector<IWSearchRule>;

    class ExtendedSketchImpl;
    using ExtendedSketch = std::shared_ptr<ExtendedSketchImpl>;
    using ExtendedSketchList = std::vector<ExtendedSketch>;
}

#endif
