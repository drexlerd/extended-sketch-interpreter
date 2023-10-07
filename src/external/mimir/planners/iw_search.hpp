#if !defined(PLANNERS_IW_SEARCH_HPP_)
#define PLANNERS_IW_SEARCH_HPP_

#include "search_space.hpp"
#include "state_registry.hpp"
#include "atom_registry.hpp"
#include "goal_test.hpp"
#include "state_data.hpp"

#include "../../dlplan/include/dlplan/novelty.h"

#include "../formalism/action.hpp"
#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"
#include "../generators/successor_generator_factory.hpp"

#include <vector>
#include <deque>

namespace mimir::planners
{
  class IWSearch
  {
  protected:
    formalism::ProblemDescription problem_;
    planners::SuccessorGenerator successor_generator_;
    std::shared_ptr<GoalTest> goal_test_;  // make unique_ptr out of this
    int max_arity_;
    bool print_;

  protected:
    /// @brief Spezialized implementation because there is no search at all.
    /// @return
    bool width_zero_search(
        const formalism::State& initial_state,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        formalism::State &final_state);

    bool width_arity_search(
        const formalism::State& initial_state,
        int arity,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        formalism::State &final_state);

  public:
    uint32_t pruned;
    uint32_t generated;
    uint32_t expanded;
    uint32_t max_expanded;
    int effective_arity;

    int64_t time_successors_ns;
    int64_t time_apply_ns;
    int64_t time_goal_test_ns;
    int64_t time_grounding_ns;
    int64_t time_search_ns;
    int64_t time_total_ns;

    IWSearch(
        const formalism::ProblemDescription &problem,
        planners::SuccessorGeneratorType successor_generator_type,
        std::shared_ptr<GoalTest>&& goal_test,
        int max_arity);
    virtual ~IWSearch() = default;

    /// @brief Finds a plan from the initial state.
    /// @return true iff a plan was found.
    virtual bool find_plan(std::vector<formalism::Action> &plan);

    virtual bool find_plan(const formalism::State& initial_state, std::vector<formalism::Action> &plan, formalism::State& final_state);

    void print_statistics() const;

    std::shared_ptr<GoalTest> get_goal_test() const;
  };
} // namespace planners

#endif // PLANNERS_IW_SEARCH_HPP_
