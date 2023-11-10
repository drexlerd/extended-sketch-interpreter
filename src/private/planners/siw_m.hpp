#ifndef SRC_PRIVATE_PLANNERS_SIW_M_HPP_
#define SRC_PRIVATE_PLANNERS_SIW_M_HPP_

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"
#include "../formalism/domain.hpp"
#include "../extended_sketch/declarations.hpp"

#include "../planners/iw_search.hpp"


namespace mimir::extended_sketch {

class SIWMSearch {
private:
    mimir::formalism::DomainDescription m_domain;
    mimir::formalism::ProblemDescription m_problem;
    std::shared_ptr<dlplan::core::InstanceInfo> m_instance_info;
    ModuleList m_modules;
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

    SIWMSearch(
        const mimir::formalism::DomainDescription& domain,
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo> instance_info,
        const extended_sketch::ModuleList& modules);

    bool find_plan(std::vector<mimir::formalism::Action>& plan);

    void print_statistics(int num_indent=0) const;
};

}

#endif