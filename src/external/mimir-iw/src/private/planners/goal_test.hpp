#if !defined(PLANNERS_GOAL_TEST_HPP_)
#define PLANNERS_GOAL_TEST_HPP_

#include <chrono>

#include "state_data.hpp"
#include "atom_registry.hpp"

#include "../formalism/problem.hpp"

#include "../dlplan/include/dlplan/core.h"
#include "../dlplan/include/dlplan/policy.h"


namespace mimir::planners {
    class GoalTest {
        protected:
            formalism::ProblemDescription problem_;

            uint32_t count_goal_test_;

        public:
            GoalTest(formalism::ProblemDescription problem) : problem_(problem), count_goal_test_(0) { }
            virtual ~GoalTest() = default;

            virtual bool test_goal(const StateData& /*state_data*/) = 0;

            virtual void set_initial_state(const StateData& /*state_data*/) { };

            virtual std::unique_ptr<AtomRegistry> get_atom_registry() const {
                return std::make_unique<AtomRegistry>(problem_);
            }

            virtual void print_statistics(int num_indent=0) const {
                auto spaces = std::vector<char>(num_indent, ' ');
                std::string indent(spaces.begin(), spaces.end());
                std::cout << indent << "Num goal tests: " << count_goal_test_ << std::endl;
            }
    };


    class TopGoalTest : public GoalTest {
        private:
            uint64_t time_top_goal_ns_;

        public:
            TopGoalTest(formalism::ProblemDescription problem) : GoalTest(problem), time_top_goal_ns_(0) { }
            virtual ~TopGoalTest() = default;

            virtual bool test_goal(const StateData& state_data) override {
                ++count_goal_test_;
                const auto start = std::chrono::high_resolution_clock::now();
                bool is_goal = literals_hold(problem_->goal, state_data.state);
                const auto end = std::chrono::high_resolution_clock::now();
                time_top_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                return is_goal;
            }

            virtual void print_statistics(int num_indent=0) const override {
                auto spaces = std::vector<char>(num_indent, ' ');
                std::string indent(spaces.begin(), spaces.end());
                std::cout << indent << "Top goal time: " << time_top_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
            }
    };


    class CountGoalTest : public GoalTest {
        private:
            int num_unsatisfied_goal_literals_;

            uint64_t time_count_top_goal_ns_;

        public:
            CountGoalTest(formalism::ProblemDescription problem) : GoalTest(problem), num_unsatisfied_goal_literals_(0), time_count_top_goal_ns_(0) { }
            virtual ~CountGoalTest() = default;

            virtual bool test_goal(const StateData& state_data) override {
                ++count_goal_test_;
                const auto start = std::chrono::high_resolution_clock::now();
                int num_unsatisfied_goal_literals = compute_num_unsatisfied_literals(problem_->goal, state_data.state);
                bool is_goal = (num_unsatisfied_goal_literals < num_unsatisfied_goal_literals_);
                const auto end = std::chrono::high_resolution_clock::now();
                time_count_top_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                return is_goal;
            }

            virtual void set_initial_state(const StateData& state_data) override {
                num_unsatisfied_goal_literals_ = compute_num_unsatisfied_literals(problem_->goal, state_data.state);
            }

            virtual void print_statistics(int num_indent=0) const override {
                auto spaces = std::vector<char>(num_indent, ' ');
                std::string indent(spaces.begin(), spaces.end());
                std::cout << indent << "Count top goal time: " << time_count_top_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
            }
    };


    class SketchGoalTest : public GoalTest {
        protected:
            std::shared_ptr<dlplan::core::InstanceInfo> instance_;
            std::shared_ptr<const dlplan::policy::Policy> sketch_;

            std::unique_ptr<dlplan::core::State> dlplan_initial_state_;
            dlplan::core::DenotationsCaches caches_;
            std::vector<std::shared_ptr<const dlplan::policy::Rule>> applicable_rules_;

            uint64_t time_top_goal_ns_;
            uint64_t time_sketch_goal_ns_;

        public:
            SketchGoalTest(
                formalism::ProblemDescription problem,
                std::shared_ptr<dlplan::core::InstanceInfo> instance,
                const std::shared_ptr<const dlplan::policy::Policy>& sketch) : GoalTest(problem), instance_(instance), sketch_(sketch), time_top_goal_ns_(0), time_sketch_goal_ns_(0) {
                }

            virtual bool test_goal(const StateData& state_data) override {
                if (sketch_ == nullptr) {
                    throw std::runtime_error("SketchGoalTest::test_goal - no sketch, call set_initial_state first.");
                }
                ++count_goal_test_;
                const auto start_top_goal = std::chrono::high_resolution_clock::now();
                bool is_goal = literals_hold(problem_->goal, state_data.state);
                const auto end_top_goal = std::chrono::high_resolution_clock::now();
                time_top_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end_top_goal - start_top_goal).count();
                if (is_goal) {
                    return true;
                }
                const auto start_sketch_goal = std::chrono::high_resolution_clock::now();
                dlplan::core::State dlplan_target_state(instance_, state_data.state_atom_indices, state_data.register_contents, state_data.state_index);
                is_goal = (sketch_->evaluate_effects(*dlplan_initial_state_, dlplan_target_state, applicable_rules_, caches_) != nullptr);
                const auto end_sketch_goal = std::chrono::high_resolution_clock::now();
                time_sketch_goal_ns_ += std::chrono::duration_cast<std::chrono::nanoseconds>(end_sketch_goal - start_sketch_goal).count();
                if (is_goal) {
                    return true;
                }
                return false;
            }

            virtual void set_initial_state(const StateData& state_data) override {
                dlplan_initial_state_ = std::make_unique<dlplan::core::State>(instance_, state_data.state_atom_indices, state_data.state_index);
                caches_ = dlplan::core::DenotationsCaches();
                applicable_rules_ = sketch_->evaluate_conditions(*dlplan_initial_state_, caches_);
                if (applicable_rules_.empty()) {
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

            virtual std::unique_ptr<AtomRegistry> get_atom_registry() const override{
                return std::make_unique<DLPlanAtomRegistry>(problem_, instance_);
            }

            virtual void print_statistics(int num_indent=0) const override {
                auto spaces = std::vector<char>(num_indent, ' ');
                std::string indent(spaces.begin(), spaces.end());
                GoalTest::print_statistics(num_indent);
                std::cout << indent << "Top goal time: " << time_top_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
                std::cout << indent << "Sketch goal time: " << time_sketch_goal_ns_  / (int64_t) 1E6 << " ms" << std::endl;
            }
    };
}


#endif