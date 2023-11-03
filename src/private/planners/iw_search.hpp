#if !defined(PLANNERS_IW_SEARCH_HPP_)
#define PLANNERS_IW_SEARCH_HPP_

#include "search_space.hpp"
#include "state_registry.hpp"
#include "atom_registry.hpp"
#include "goal_test.hpp"
#include "state_data.hpp"
#include "random_generator.hpp"

#include "src/private/extended_sketch/extended_state.hpp"

#include "../dlplan/include/dlplan/novelty.h"

#include "../formalism/action.hpp"
#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"
#include "../generators/successor_generator_factory.hpp"

#include <vector>
#include <deque>
#include <unordered_map>


namespace mimir::planners
{
  class IWSearch
  {
  protected:
    formalism::ProblemDescription problem_;
    std::shared_ptr<dlplan::core::InstanceInfo> instance_info_;
    planners::SuccessorGenerator successor_generator_;
    ExtendedSketchGoalTest goal_test_;
    int max_arity_;
    bool print_;
    std::shared_ptr<RandomGenerator> random_generator_;
    int g_value_;
    std::vector<int> g_values_;

  protected:
    /// @brief Spezialized implementation because there is no search at all.
    /// @return
    bool width_zero_search(
        const mimir::extended_sketch::ExtendedState& initial_state,
        mimir::extended_sketch::ExtendedState& final_state,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        std::shared_ptr<const dlplan::policy::Rule>& reason);

    bool width_arity_search(
        const mimir::extended_sketch::ExtendedState& initial_state,
        mimir::extended_sketch::ExtendedState& final_state,
        int arity,
        StateRegistry& state_registry,
        AtomRegistry& atom_registry,
        std::vector<formalism::Action> &plan,
        std::shared_ptr<const dlplan::policy::Rule>& reason);

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
        const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
        planners::SuccessorGeneratorType successor_generator_type,
        const std::unordered_map<mimir::extended_sketch::MemoryState, std::shared_ptr<const dlplan::policy::Policy>>& sketches_by_memory_state,
        int max_arity);
    virtual ~IWSearch();

    virtual bool find_plan(
      const mimir::extended_sketch::ExtendedState& initial_state,
      mimir::extended_sketch::ExtendedState& final_state,
      std::vector<formalism::Action> &plan,
      std::shared_ptr<const dlplan::policy::Rule>& reason);

    void print_statistics(int num_indent=0) const;

    const ExtendedSketchGoalTest& get_goal_test() const;
  };
} // namespace planners

#endif // PLANNERS_IW_SEARCH_HPP_
