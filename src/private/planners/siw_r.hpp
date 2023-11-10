#ifndef SRC_PRIVATE_PLANNERS_SIW_R_HPP_
#define SRC_PRIVATE_PLANNERS_SIW_R_HPP_

#include "iw_search_statistics.hpp"

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"
#include "../formalism/domain.hpp"
#include "../extended_sketch/declarations.hpp"

#include "../planners/iw_search.hpp"


namespace mimir::planners {

class SIWRSearch {
private:
    mimir::formalism::DomainDescription m_domain;
    mimir::formalism::ProblemDescription m_problem;
    std::shared_ptr<dlplan::core::InstanceInfo> m_instance_info;
    mimir::extended_sketch::ExtendedSketch m_extended_sketch;

    planners::SuccessorGenerator m_successor_generator;
    int m_max_arity;

public:
    IWSearchStatistics statistics;

    float average_effective_arity;
    int maximum_effective_arity;

    SIWRSearch(
        const mimir::formalism::DomainDescription& domain,
        const mimir::formalism::ProblemDescription& problem,
        const std::shared_ptr<dlplan::core::InstanceInfo> instance_info,
        const extended_sketch::ExtendedSketch& extended_sketch,
        planners::SuccessorGeneratorType successor_generator_type,
        int max_arity);

    bool find_plan(std::vector<mimir::formalism::Action>& plan);

    void print_statistics(int num_indent=0) const;
};

}

#endif