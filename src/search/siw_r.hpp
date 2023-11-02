#ifndef SRC_SEARCH_SIW_R_HPP_
#define SRC_SEARCH_SIW_R_HPP_

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/extended_sketch/declarations.hpp"

#include "src/external/mimir-iw/src/private/planners/iw_search.hpp"


namespace sketches::extended_sketch {

class SIWRSearch {
private:
    mimir::formalism::DomainDescription m_domain;
    mimir::formalism::ProblemDescription m_problem;
    std::shared_ptr<dlplan::core::InstanceInfo> m_instance_info;
    std::shared_ptr<dlplan::policy::PolicyFactory> m_policy_factory;
    extended_sketch::ExtendedSketch m_extended_sketch;
    std::unique_ptr<mimir::planners::IWSearch> m_iw_search;

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