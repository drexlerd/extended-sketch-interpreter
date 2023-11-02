#ifndef SRC_SEARCH_GOAL_TEST_HPP_
#define SRC_SEARCH_GOAL_TEST_HPP_

#include "src/extended_sketch/declarations.hpp"

#include "src/external/mimir-iw/src/private/planners/goal_test.hpp"
#include "src/external/mimir-iw/src/private/planners/atom_registry.hpp"

#include <unordered_map>


namespace sketches::extended_sketch {

class ExtendedSketchGoalTest : public mimir::planners::SketchGoalTest {
private:
    std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> sketches_by_memory_state_;

public:
    ExtendedSketchGoalTest(
        mimir::formalism::ProblemDescription problem,
        std::shared_ptr<dlplan::core::InstanceInfo> instance,
        std::unordered_map<MemoryState, std::shared_ptr<const dlplan::policy::Policy>> sketches_by_memory_state)
        : SketchGoalTest(problem, instance, nullptr),
          sketches_by_memory_state_(sketches_by_memory_state) {
        std::cout << "ExtendedSketchGoalTest" << std::endl;
        for (const auto& pair : sketches_by_memory_state_) {
            std::cout << pair.second->str() << std::endl << std::endl;
        }
    }

    virtual void set_initial_state(const mimir::planners::StateData& state_data) override {
        auto it = sketches_by_memory_state_.find(state_data.memory_state);
        if (it == sketches_by_memory_state_.end()) {
            throw std::runtime_error("ExtendedSketchGoalTest::set_initial_state - no sketch exists for memory state");
        }
        sketch_ = it->second;

        mimir::planners::SketchGoalTest::set_initial_state(state_data);
    };
};
}

#endif