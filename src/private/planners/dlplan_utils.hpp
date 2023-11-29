#if !defined(PLANNERS_DLPLAN_UTILS_HPP_)
#define PLANNERS_DLPLAN_UTILS_HPP_

#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"

#include <memory>


namespace mimir::planners {

extern std::string to_string(
    const dlplan::core::InstanceInfo& instance_info,
    const dlplan::core::ConceptDenotation& denotation);

extern std::string to_string(
    const dlplan::core::InstanceInfo& instance_info,
    const dlplan::core::RoleDenotation& denotation);

}

#endif
