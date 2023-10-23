#include "atom_registry.hpp"

#include <algorithm>


namespace mimir::planners {
    AtomRegistry::AtomRegistry(formalism::ProblemDescription problem)
      : problem_(problem),
        reached_rank_to_atom_index_(problem->num_ranks(), -1),
        num_reached_ranks_(0) { }

    StateData AtomRegistry::convert_state(formalism::State state, uint32_t state_index) {
        const auto ranks = state->get_dynamic_ranks();
        std::vector<int> atom_indices;
        atom_indices.reserve(ranks.size());
        for (uint32_t rank : ranks)
        {
            if (rank >= reached_rank_to_atom_index_.size()) {
                reached_rank_to_atom_index_.resize(rank + 1, -1);
            }
            if (reached_rank_to_atom_index_[rank] == -1)
            {
                reached_rank_to_atom_index_[rank] = num_reached_ranks_;
                ++num_reached_ranks_;
            }
            int atom_index = reached_rank_to_atom_index_[rank];
            atom_indices.push_back(atom_index);
        }
        std::sort(atom_indices.begin(), atom_indices.end());
        return StateData{state, atom_indices, state_index};
    }

    int AtomRegistry::get_num_reached_ranks() const {
        return num_reached_ranks_;
    }


    DLPlanAtomRegistry::DLPlanAtomRegistry(
        formalism::ProblemDescription problem,
        std::shared_ptr<dlplan::core::InstanceInfo> instance)
        : AtomRegistry(problem), instance_(instance) {
            instance_->clear_atoms();
        }

    StateData DLPlanAtomRegistry::convert_state(formalism::State state, uint32_t state_index) {
        const auto ranks = state->get_dynamic_ranks();
        std::vector<int> atom_indices;
        atom_indices.reserve(ranks.size());
        for (uint32_t rank : ranks) {
            if (rank >= reached_rank_to_atom_index_.size()) {
                reached_rank_to_atom_index_.resize(rank + 1, -1);
            }
            if (reached_rank_to_atom_index_[rank] == -1) {
                reached_rank_to_atom_index_[rank] = num_reached_ranks_;
                const auto atom = problem_->get_atom(rank);
                std::vector<std::string> object_names;
                for (const auto object : atom->arguments) {
                    object_names.push_back(object->name);
                }
                const auto& dlplan_atom = instance_->add_atom(atom->predicate->name, object_names);
                assert(dlplan_atom.get_index() == num_reached_ranks_);
                ++num_reached_ranks_;
            }
            int atom_index = reached_rank_to_atom_index_[rank];
            atom_indices.push_back(atom_index);
        }
        std::sort(atom_indices.begin(), atom_indices.end());
        return StateData{state, atom_indices, state_index};
    }
}