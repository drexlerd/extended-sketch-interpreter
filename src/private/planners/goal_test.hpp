#ifndef SRC_SEARCH_GOAL_TEST_HPP_
#define SRC_SEARCH_GOAL_TEST_HPP_

#include "../extended_sketch/declarations.hpp"

#include "../formalism/state.hpp"
#include "state_data.hpp"

#include <unordered_map>
#include <chrono>


namespace mimir::planners {

struct GoalTestResult {
    bool is_goal;
    std::shared_ptr<const dlplan::policy::Rule> reason;
};


class ExtendedSketchGoalTest {
private:
    mimir::formalism::ProblemDescription problem_;
    std::shared_ptr<dlplan::core::InstanceInfo> instance_;

    std::unordered_map<mimir::extended_sketch::MemoryState, std::shared_ptr<const dlplan::policy::Policy>> sketches_by_memory_state_;
    std::shared_ptr<const dlplan::policy::Policy> sketch_;

    std::shared_ptr<const dlplan::core::State> dlplan_initial_state_;
    dlplan::core::DenotationsCaches caches_;
    std::vector<std::shared_ptr<const dlplan::policy::Rule>> applicable_rules_;

    uint32_t count_goal_test_;
    uint64_t time_top_goal_ns_;
    uint64_t time_sketch_goal_ns_;

public:
    ExtendedSketchGoalTest(
        mimir::formalism::ProblemDescription problem,
        std::shared_ptr<dlplan::core::InstanceInfo> instance,
        std::unordered_map<mimir::extended_sketch::MemoryState, std::shared_ptr<const dlplan::policy::Policy>> sketches_by_memory_state)
        : problem_(problem), instance_(instance),
          sketches_by_memory_state_(sketches_by_memory_state), sketch_(nullptr),
          dlplan_initial_state_(nullptr), caches_(dlplan::core::DenotationsCaches()), applicable_rules_({}),
          count_goal_test_(0), time_top_goal_ns_(0), time_sketch_goal_ns_(0) {
    }

    GoalTestResult test_goal(const StateData& state_data) {
        if (sketch_ == nullptr) {
            throw std::runtime_error("SketchGoalTest::test_goal - no sketch, call set_initial_state first.");
        }
        bool is_goal = false;
        ++count_goal_test_;
        const auto start_sketch_goal = std::chrono::high_resolution_clock::now();
        std::shared_ptr<const dlplan::policy::Rule> reason = nullptr;
        for (const auto& rule : applicable_rules_) {
            if (rule->evaluate_effects(*dlplan_initial_state_, *state_data.extended_state.dlplan, caches_)) {
                is_goal = true;
                reason = rule;
                break;
            }
        }
        const auto end_sketch_goal = std::chrono::high_resolution_clock::now();
        time_sketch_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end_sketch_goal - start_sketch_goal).count();
        if (is_goal) {
            return GoalTestResult{true, reason};
        }

        /*
        const auto start_top_goal = std::chrono::high_resolution_clock::now();
        is_goal = literals_hold(problem_->goal, state_data.state);
        const auto end_top_goal = std::chrono::high_resolution_clock::now();
        time_top_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end_top_goal - start_top_goal).count();
        if (is_goal) {
            return GoalTestResult{true, nullptr};
        }
        */
        return GoalTestResult{false, nullptr};
    }

    void set_initial_state(const mimir::planners::StateData& state_data) {
        auto it = sketches_by_memory_state_.find(state_data.extended_state.memory);
        if (it == sketches_by_memory_state_.end()) {
            throw std::runtime_error("ExtendedSketchGoalTest::set_initial_state - no sketch exists for memory state");
        }
        sketch_ = it->second;

        dlplan_initial_state_ = state_data.extended_state.dlplan;
        caches_ = dlplan::core::DenotationsCaches();
        applicable_rules_ = sketch_->evaluate_conditions(*dlplan_initial_state_, caches_);
        if (applicable_rules_.empty()) {
            std::cout << sketch_->str() << std::endl;
            throw std::runtime_error("No rule applicable for state: " + dlplan_initial_state_->str());
        }
        /*
        std::cout << dlplan_initial_state_->str() << std::endl;
        std::cout << "Num applicable rules: " << applicable_rules_.size() << std::endl;
        for (const auto& applicable_rule : applicable_rules_) {
            std::cout << applicable_rule->str() << std::endl;
        }
        */
    };

    void print_statistics(int num_indent=0) const {
        auto spaces = std::vector<char>(num_indent, ' ');
        std::string indent(spaces.begin(), spaces.end());
        std::cout << indent << "Num goal tests: " << count_goal_test_ << std::endl;
        std::cout << indent << "Top goal time: " << time_top_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
        std::cout << indent << "Sketch goal time: " << time_sketch_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
    }
};
}

#endif