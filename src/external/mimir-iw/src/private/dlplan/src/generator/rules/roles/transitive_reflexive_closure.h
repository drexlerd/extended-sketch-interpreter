#ifndef DLPLAN_SRC_GENERATOR_RULES_ROLES_TRANSITIVE_REFLEXIVE_CLOSURE_H_
#define DLPLAN_SRC_GENERATOR_RULES_ROLES_TRANSITIVE_REFLEXIVE_CLOSURE_H_

#include "src/generator/rules/rule.h"


namespace dlplan::generator::rules {
class TransitiveReflexiveClosureRole : public Rule {
public:
    void generate_impl(const core::States& states, int target_complexity, GeneratorData& data, core::DenotationsCaches& caches) override;

    std::string get_name() const override;
};

}

#endif
