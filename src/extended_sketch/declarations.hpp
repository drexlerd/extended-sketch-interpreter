#ifndef SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_
#define SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"



namespace sketches::extended_sketch {
    using Boolean = std::shared_ptr<const dlplan::policy::NamedBoolean>;
    using BooleanList = std::vector<Boolean>;
    using BooleanMap = std::unordered_map<std::string, Boolean>;

    using Numerical = std::shared_ptr<const dlplan::policy::NamedNumerical>;
    using NumericalList = std::vector<Numerical>;
    using NumericalMap = std::unordered_map<std::string, Numerical>;

    using Concept = std::shared_ptr<const dlplan::policy::NamedConcept>;
    using ConceptList = std::vector<Concept>;
    using ConceptMap = std::unordered_map<std::string, Concept>;

    using Condition = std::shared_ptr<const dlplan::policy::BaseCondition>;
    using ConditionList = std::vector<Condition>;
    using ConditionSet = dlplan::policy::Conditions;

    using Effect = std::shared_ptr<const dlplan::policy::BaseEffect>;
    using EffectList = std::vector<Effect>;
    using EffectSet = dlplan::policy::Effects;

    class RegisterImpl;
    using Register = std::shared_ptr<RegisterImpl>;
    using RegisterList = std::vector<Register>;

    class MemoryStateImpl;
    using MemoryState = std::shared_ptr<MemoryStateImpl>;
    using MemoryStateList = std::vector<MemoryState>;

    class LoadRuleImpl;
    using LoadRule = std::shared_ptr<LoadRuleImpl>;
    using LoadRuleList = std::vector<LoadRule>;

    class CallRuleImpl;
    using CallRule = std::shared_ptr<CallRuleImpl>;
    using CallRuleList = std::vector<CallRule>;

    class ActionRuleImpl;
    using ActionRule = std::shared_ptr<ActionRuleImpl>;
    using ActionRuleList = std::vector<ActionRule>;

    class SearchRuleImpl;
    using SearchRule = std::shared_ptr<SearchRuleImpl>;
    using SearchRuleList = std::vector<SearchRule>;

    class ExtendedSketchImpl;
    using ExtendedSketch = std::shared_ptr<ExtendedSketchImpl>;

    class ExtendedStateImpl;
    using ExtendedState = std::shared_ptr<ExtendedStateImpl>;
    using ExtendedStateList = std::vector<ExtendedState>;

}

#endif
