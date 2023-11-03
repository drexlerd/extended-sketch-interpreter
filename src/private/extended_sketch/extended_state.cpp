#include "extended_state.hpp"

#include "src/private/formalism/state.hpp"
#include "src/private/planners/atom_registry.hpp"

namespace mimir::extended_sketch {

ExtendedState create_initial_state(
    const mimir::formalism::ProblemDescription& problem,
    const std::shared_ptr<dlplan::core::InstanceInfo>& instance_info,
    const MemoryState& current_memory_state,
    int num_registers) {
    std::vector<int> register_contents(num_registers, 0);
    auto current_state = mimir::formalism::create_state(problem->initial, problem);
    std::shared_ptr<const dlplan::core::State> current_dlplan_state = nullptr;
    {
        mimir::planners::DLPlanAtomRegistry atom_registry(problem, instance_info);
        current_dlplan_state = std::make_shared<dlplan::core::State>(instance_info, atom_registry.convert_state(current_state), register_contents, 0);
    }
    return ExtendedState{
        current_memory_state,
        current_state,
        current_dlplan_state
    };
}

}