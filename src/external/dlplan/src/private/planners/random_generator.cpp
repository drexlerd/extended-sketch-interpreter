#include "random_generator.hpp"

namespace planners {

RandomGenerator::RandomGenerator() {
    random_generator = std::default_random_engine(0);
}

}