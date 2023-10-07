#if !defined(PLANNERS_DLPLAN_UTILS_HPP_)
#define PLANNERS_DLPLAN_UTILS_HPP_

#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"

#include "../../dlplan/include/dlplan/core.h"
#include "../../dlplan/include/dlplan/policy.h"

#include <memory>


namespace mimir::planners {

extern std::shared_ptr<dlplan::core::VocabularyInfo> construct_vocabulary(
    const formalism::DomainDescription& domain);

extern std::shared_ptr<dlplan::core::InstanceInfo> construct_instance(
    const formalism::ProblemDescription& problem,
    std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary);

extern dlplan::policy::Policy read_sketch(
    std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary,
    const std::string& sketch_filename);
}

#endif
