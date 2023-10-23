#if !defined(PLANNERS_SEARCH_SPACE_HPP_)
#define PLANNERS_SEARCH_SPACE_HPP_

#include "../formalism/action.hpp"
#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"

#include <unordered_map>
#include <vector>


namespace planners {
    struct SearchContext {
        formalism::Action predecessor_action;
        uint32_t state_index;
        uint32_t predecessor_context_index;
        uint32_t fringe_value;
        bool is_goal_state;
        bool is_expanded;

        SearchContext(const formalism::Action& predecessor_action,
                     const uint32_t state_index,
                     const uint32_t predecessor_context_index,
                     const uint32_t fringe_value,
                     const bool is_goal_state,
                     const bool is_expanded) :
            predecessor_action(predecessor_action),
            state_index(state_index),
            predecessor_context_index(predecessor_context_index),
            fringe_value(fringe_value),
            is_goal_state(is_goal_state),
            is_expanded(is_expanded)
        {
        }
    };

    /// @brief SearchSpace defines a graph where each node represents a unique state
    ///        with additional search info. The state indices can be sparse.
    class SearchSpace {
        private:
            std::vector<SearchContext> context_by_index_;

        public:
            uint32_t add_context(SearchContext context);
            SearchContext& get_context(uint32_t index);
            const SearchContext& get_context(uint32_t index) const;
            void set_context(uint32_t index, SearchContext context);

            void set_plan(uint32_t context_index, std::vector<formalism::Action>& plan) const;
    };


    /// @brief Keep track of visited states by their index.
    class StateToContextIndex {
        private:
            std::vector<uint32_t> state_to_context_;

        public:
            uint32_t get_context_index(uint32_t state_index);
            void set_context_index(uint32_t state_index, uint32_t context_index);

            static const uint32_t not_exists;
    };
}

#endif