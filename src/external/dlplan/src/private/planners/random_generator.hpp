#if !defined(PLANNERS_RANDOM_GENERATOR_HPP_)
#define PLANNERS_RANDOM_GENERATOR_HPP_

#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"

#include <memory>
#include <random>


namespace planners {

struct RandomGenerator {
    std::random_device random_device;
    std::default_random_engine random_generator;

    RandomGenerator();
};

}

#endif
