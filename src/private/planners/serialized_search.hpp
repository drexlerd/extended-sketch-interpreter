#if !defined(PLANNERS_SERIALIZED_SEARCH_HPP_)
#define PLANNERS_SERIALIZED_SEARCH_HPP_

#include "../formalism/problem.hpp"

#include "iw_search.hpp"

#include <iomanip>


namespace mimir::planners {
    class SerializedSearch {
        private:
            formalism::ProblemDescription problem_;
            IWSearch inner_search_;

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

            SerializedSearch(
                const formalism::ProblemDescription& problem,
                IWSearch&& inner_search)
                : problem_(problem),
                  inner_search_(std::move(inner_search)) {
                time_grounding_ns = inner_search_.time_grounding_ns;
            }

            bool find_plan(std::vector<formalism::Action>& plan) {
                pruned = 0;
                generated = 0;
                expanded = 0;
                time_successors_ns = 0;
                time_apply_ns = 0;
                time_goal_test_ns = 0;
                time_search_ns = 0;
                time_total_ns = 0;
                average_effective_arity = 0;
                maximum_effective_arity = 0;

                const auto time_start = std::chrono::high_resolution_clock::now();

                std::vector<formalism::Action> partial_plan;
                int count_partial_solutions = 0;
                formalism::State current_state = formalism::create_state(problem_->initial, problem_);
                assert(current_state);
                bool fail = false;
                do {
                    ++count_partial_solutions;
                    formalism::State final_state;
                    bool found_partial_solution = inner_search_.find_plan(current_state, {}, nullptr, partial_plan, final_state);
                    pruned += inner_search_.pruned;
                    generated += inner_search_.generated;
                    expanded += inner_search_.expanded;
                    time_successors_ns += inner_search_.time_successors_ns;
                    time_apply_ns += inner_search_.time_apply_ns;
                    time_goal_test_ns += inner_search_.time_goal_test_ns;
                    if (found_partial_solution) {
                        plan.insert(plan.end(), partial_plan.begin(), partial_plan.end());
                        current_state = final_state;
                        average_effective_arity += inner_search_.effective_arity;
                        maximum_effective_arity = std::max(maximum_effective_arity, inner_search_.effective_arity);
                        std::cout << std::endl;
                        std::cout << count_partial_solutions << ". Inner IW search statistics:" << std::endl;
                        inner_search_.print_statistics(4);
                        std::cout << "    Plan length: " << partial_plan.size() << std::endl;

                        /*
                        std::cout << "Final state: " << final_state->get_dynamic_atoms() << std::endl;
                        for (const auto& action : partial_plan)
                        {
                            std::cout << action << std::endl;
                        }*/

                    } else {
                        average_effective_arity = std::numeric_limits<float>::max();
                        maximum_effective_arity = std::numeric_limits<int>::max();
                        fail = true;
                        break;
                    }
                } while (!literals_hold(problem_->goal, current_state));

                average_effective_arity /= count_partial_solutions;
                const auto time_end = std::chrono::high_resolution_clock::now();
                time_search_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();
                time_total_ns = inner_search_.time_grounding_ns + time_search_ns;
                if (fail) return false;
                return true;
        }

        void print_statistics(int num_indent=0) const {
            auto spaces = std::vector<char>(num_indent, ' ');
            std::string indent(spaces.begin(), spaces.end());
            std::cout << indent << "Expanded " << expanded << " states" << std::endl;
            std::cout << indent << "Generated " << generated << " states" << std::endl;
            std::cout << indent << "Pruned " << pruned << " states" << std::endl;
            std::cout << indent << "Average effective width " << average_effective_arity << std::endl;
            std::cout << indent << "Maximum effective width " << maximum_effective_arity << std::endl;
            std::cout << indent << "Successor time: " << time_successors_ns / (int64_t) 1E6 << " ms"
                    << " (" << std::fixed << std::setprecision(3) << (100.0 * time_successors_ns) / time_total_ns << "%)" << std::endl;
            std::cout << indent << "Apply time: " << time_apply_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_apply_ns) / time_total_ns << "%)" << std::endl;
            std::cout << indent << "Grounding time: " << time_grounding_ns / (int64_t) 1E6 << " ms"
                    << " (" << std::fixed << std::setprecision(3) << (100.0 * time_grounding_ns) / time_total_ns << "%)" << std::endl;
            std::cout << indent << "Goal time: " << time_goal_test_ns / (int64_t) 1E6 << " ms"
                    << " (" << std::fixed << std::setprecision(3) << (100.0 * time_goal_test_ns) / time_total_ns << "%)" << std::endl;
            std::cout << indent << "Search time: " << time_search_ns / (int64_t) 1E6 << " ms" << std::endl;
            std::cout << indent << "Total time: " << time_total_ns / (int64_t) 1E6 << " ms" << std::endl;
        }
    };
}

#endif