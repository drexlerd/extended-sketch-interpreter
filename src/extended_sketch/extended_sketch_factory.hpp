#ifndef SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_FACTORY_HPP_
#define SRC_EXTENDED_SKETCH_EXTENDED_SKETCH_FACTORY_HPP_

#include "src/external/mimir-iw/src/private/formalism/declarations.hpp"
#include "declarations.hpp"

#include "cache.hpp"


namespace sketches::extended_sketch {

class ExtendedSketchFactory {
private:
    Caches m_caches;

public:
    ExtendedSketchFactory();

    LoadRule make_load_rule(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const Register& reg,
        const Concept& concept);

    CallRule make_call_rule(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const std::string& extended_sketch_name,
        const RegisterList& arguments);

    ActionRule make_action_rule(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects,
        const mimir::formalism::ActionSchema& action_schema,
        const RegisterList& arguments);

    SearchRule make_search_rule(
        const MemoryState& memory_state_condition,
        const MemoryState& memory_state_effect,
        const ConditionSet& feature_conditions,
        const EffectSet& feature_effects);
};

}

#endif
