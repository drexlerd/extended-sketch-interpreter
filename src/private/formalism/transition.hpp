#if !defined(FORMALISM_TRANSITION_HPP_)
#define FORMALISM_TRANSITION_HPP_

#include "action.hpp"
#include "declarations.hpp"

#include <memory>

namespace mimir::formalism
{
    class TransitionImpl
    {
      public:
        formalism::State source_state;
        formalism::State target_state;
        formalism::Action action;

        TransitionImpl(const formalism::State& source_state, const formalism::Action& action, const formalism::State& target_state);
    };

    Transition create_transition(const formalism::State& source_state, const formalism::Action& action, const formalism::State& target_state);

    StateTransitions to_state_transitions(const formalism::ProblemDescription& problem, const formalism::TransitionList& transitions);

    std::ostream& operator<<(std::ostream& os, const formalism::Transition& transition);

    std::ostream& operator<<(std::ostream& os, const formalism::TransitionList& transitions);

}  // namespace formalism

namespace std
{
    // Inject comparison and hash functions to make pointers behave appropriately with ordered and unordered datastructures
    template<>
    struct hash<mimir::formalism::Transition>
    {
        std::size_t operator()(const mimir::formalism::Transition& transition) const;
    };

    template<>
    struct less<mimir::formalism::Transition>
    {
        bool operator()(const mimir::formalism::Transition& left_transition, const mimir::formalism::Transition& right_transition) const;
    };

    template<>
    struct equal_to<mimir::formalism::Transition>
    {
        bool operator()(const mimir::formalism::Transition& left_transition, const mimir::formalism::Transition& right_transition) const;
    };

}  // namespace std

#endif  // FORMALISM_TRANSITION_HPP_
