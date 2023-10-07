#if !defined(PLANNERS_ATOM_REGISTRY_HPP_)
#define PLANNERS_ATOM_REGISTRY_HPP_

#include "state_data.hpp"

#include "../formalism/problem.hpp"

#include "../../dlplan/include/dlplan/core.h"

#include <vector>
#include <memory>

namespace mimir::planners {
    /// @brief Registers atoms reached by a state and computes a sparse indexing scheme.
    class AtomRegistry {
        protected:
            formalism::ProblemDescription problem_;

            std::vector<int> reached_rank_to_atom_index_;
            uint32_t num_reached_ranks_;

        public:
            AtomRegistry(formalism::ProblemDescription problem);
            virtual ~AtomRegistry() = default;

            virtual StateData convert_state(formalism::State state, uint32_t state_index);

            int get_num_reached_ranks() const;
    };

    /// @brief Additionally instantiates DLPlan atoms.
    class DLPlanAtomRegistry : public AtomRegistry {
        protected:
            std::shared_ptr<dlplan::core::InstanceInfo> instance_;

        public:
            DLPlanAtomRegistry(formalism::ProblemDescription problem, std::shared_ptr<dlplan::core::InstanceInfo> instance);
            virtual ~DLPlanAtomRegistry() = default;

            virtual StateData convert_state(formalism::State state, uint32_t state_index) override;
    };
}

#endif