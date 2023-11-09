#ifndef SRC_PRIVATE_PLANNERS_SIW_R_HPP_
#define SRC_PRIVATE_PLANNERS_SIW_R_HPP_

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"
#include "../formalism/domain.hpp"
#include "../extended_sketch/declarations.hpp"

#include "../planners/iw_search.hpp"


namespace mimir::extended_sketch {

class SIWRSearch {
private:
    mimir::formalism::DomainDescription m_domain;
    mimir::formalism::ProblemDescription m_problem;
    std::shared_ptr<dlplan::core::InstanceInfo> m_instance_info;
    std::shared_ptr<dlplan::policy::PolicyFactory> m_policy_factory;
    ExtendedSketch m_extended_sketch;
    std::unique_ptr<mimir::planners::IWSearch> m_iw_search;

    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> m_sketches_by_memory_state;
    std::unordered_map<std::shared_ptr<const dlplan::policy::Rule>, MemoryState> m_rule_to_memory_effect;
    std::unordered_map<MemoryState, std::vector<LoadRule>> m_load_rules_by_memory_state;
    std::unordered_map<Register, int> m_register_mapping;

private:
    bool try_apply_load_rule(
        const ExtendedState& current_state,
        int& step,
        ExtendedState& successor_state);

    bool try_apply_search_rule(
        const ExtendedState& current_state,
        int& step,
        ExtendedState& successor_state);

public:
    uint32_t pruned;
    uint32_t generated;
    uint32_t expanded;
    uint32_t max_expanded;
    int effective_arity;
    float average_effective_arity;
    int maximum_effective_arity;

    int64_t time_successors_ns;
    int64_t time_apply_ns;
    int64_t time_grounding_ns;
    int64_t time_goal_test_ns;
    int64_t time_search_ns;
    int64_t time_total_ns;

    SIWRSearch(
        const mimir::formalism::DomainDescription& domain,
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo> instance_info,
        const std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory,
        const extended_sketch::ExtendedSketch& extended_sketch);

    bool find_plan(std::vector<mimir::formalism::Action>& plan);

    void print_statistics(int num_indent=0) const;
};

}

#endif