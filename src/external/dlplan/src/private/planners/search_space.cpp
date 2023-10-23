#include "search_space.hpp"

#include <algorithm>
#include <cassert>
#include <limits>

namespace planners {
    uint32_t SearchSpace::add_context(SearchContext context) {
        int context_index = context_by_index_.size();
        context_by_index_.push_back(context);
        return context_index;
    }

    SearchContext& SearchSpace::get_context(uint32_t index) {
        assert(index < context_by_index_.size());
        return context_by_index_.at(index);
    }

    const SearchContext& SearchSpace::get_context(uint32_t index) const {
        assert(index < context_by_index_.size());
        return context_by_index_.at(index);
    }

    void SearchSpace::set_context(uint32_t index, SearchContext context) {
        assert(index < context_by_index_.size());
        context_by_index_[index] = context;
    }

    void SearchSpace::set_plan(uint32_t context_index, std::vector<formalism::Action>& plan) const {
        assert(context_index < context_by_index_.size());
        plan.clear();
        auto current_context_index = context_index;
        while (true)
        {
            const auto& current_context = context_by_index_[current_context_index];
            const auto predecessor_action = current_context.predecessor_action;

            if (predecessor_action == nullptr)
            {
                break;
            }

            plan.push_back(predecessor_action);
            current_context_index = current_context.predecessor_context_index;
        }
        std::reverse(plan.begin(), plan.end());
    }


    uint32_t StateToContextIndex::get_context_index(uint32_t state_index) {
        if (state_to_context_.size() <= state_index) {
            state_to_context_.resize(state_index + 1, StateToContextIndex::not_exists);
        }
        return state_to_context_[state_index];
    }

    void StateToContextIndex::set_context_index(uint32_t state_index, uint32_t context_index) {
        if (state_to_context_.size() <= state_index) {
            state_to_context_.resize(state_index + 1, StateToContextIndex::not_exists);
        }
        state_to_context_[state_index] = context_index;
    }

    const uint32_t StateToContextIndex::not_exists = std::numeric_limits<uint32_t>::max();
}