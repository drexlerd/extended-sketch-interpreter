#ifndef SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_
#define SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"


namespace sketches::extended_sketch {
    class MemoryStateImpl;
    using MemoryState = std::shared_ptr<MemoryStateImpl>;
    using MemoryStateList = std::vector<MemoryState>;
    using MemoryStateMap = std::unordered_map<std::string, MemoryState>;

    class RegisterImpl;
    using Register = std::shared_ptr<RegisterImpl>;
    using RegisterList = std::vector<Register>;
    using RegisterMap = std::unordered_map<std::string, Register>;

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

    class LoadRuleImpl;
    using LoadRule = std::shared_ptr<const LoadRuleImpl>;
    using LoadRuleList = std::vector<LoadRule>;
    using LoadRuleSet = std::set<LoadRule, dlplan::policy::ScoreCompare<LoadRule>>;

    class CallRuleImpl;
    using CallRule = std::shared_ptr<const CallRuleImpl>;
    using CallRuleList = std::vector<CallRule>;

    class ActionRuleImpl;
    using ActionRule = std::shared_ptr<const ActionRuleImpl>;
    using ActionRuleList = std::vector<ActionRule>;

    class SearchRuleImpl;
    using SearchRule = std::shared_ptr<const SearchRuleImpl>;
    using SearchRuleList = std::vector<SearchRule>;

    class ExtendedStateImpl;
    using ExtendedState = std::shared_ptr<ExtendedStateImpl>;
    using ExtendedStateList = std::vector<ExtendedState>;

    class ExtendedSketchImpl;
    using ExtendedSketch = std::shared_ptr<ExtendedSketchImpl>;
    using ExtendedSketchList = std::vector<ExtendedSketch>;
    using ExtendedSketchMap = std::unordered_map<std::string, ExtendedSketch>;
}

#endif
