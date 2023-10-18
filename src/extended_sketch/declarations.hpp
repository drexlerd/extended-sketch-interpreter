#ifndef SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_
#define SRC_EXTENDED_SKETCH_DECLARATIONS_HPP_

#include <memory>
#include <unordered_map>
#include <vector>

#include "src/external/dlplan/include/dlplan/policy.h"


namespace sketches::extended_sketch {
    class MemoryStateImpl;
    using MemoryState = std::shared_ptr<MemoryStateImpl>;
    using MemoryStateList = std::vector<MemoryState>;
    using MemoryStateMap = std::unordered_map<std::string, MemoryState>;

    class RegisterImpl;
    using Register = std::shared_ptr<RegisterImpl>;
    using RegisterList = std::vector<Register>;
    using RegisterMap = std::unordered_map<std::string, Register>;

    class BooleanImpl;
    using Boolean = std::shared_ptr<BooleanImpl>;
    using BooleanList = std::vector<Boolean>;
    using BooleanMap = std::unordered_map<std::string, Boolean>;

    class NumericalImpl;
    using Numerical = std::shared_ptr<NumericalImpl>;
    using NumericalList = std::vector<Numerical>;
    using NumericalMap = std::unordered_map<std::string, Numerical>;

    class ConceptImpl;
    using Concept = std::shared_ptr<ConceptImpl>;
    using ConceptList = std::vector<Concept>;
    using ConceptMap = std::unordered_map<std::string, Concept>;

    using Condition = std::shared_ptr<const dlplan::policy::BaseCondition>;
    using ConditionList = std::vector<Condition>;
    using ConditionSet = dlplan::policy::Conditions;

    using Effect = std::shared_ptr<const dlplan::policy::BaseEffect>;
    using EffectList = std::vector<Effect>;
    using EffectSet = dlplan::policy::Effects;

    class LoadRuleImpl;
    using LoadRule = std::shared_ptr<LoadRuleImpl>;
    using LoadRuleList = std::vector<LoadRule>;
    using LoadRuleSet = std::set<LoadRule, dlplan::policy::ScoreCompare<LoadRule>>;

    class CallRuleImpl;
    using CallRule = std::shared_ptr<CallRuleImpl>;
    using CallRuleList = std::vector<CallRule>;

    class ActionRuleImpl;
    using ActionRule = std::shared_ptr<ActionRuleImpl>;
    using ActionRuleList = std::vector<ActionRule>;

    class ExtendedStateImpl;
    using ExtendedState = std::shared_ptr<ExtendedStateImpl>;
    using ExtendedStateList = std::vector<ExtendedState>;

    class SearchRuleImpl;
    using SearchRule = std::shared_ptr<SearchRuleImpl>;
    using SearchRuleList = std::vector<SearchRule>;

    class ExtendedSketchImpl;
    using ExtendedSketch = std::shared_ptr<ExtendedSketchImpl>;
    using ExtendedSketchList = std::vector<ExtendedSketch>;
}

#endif
