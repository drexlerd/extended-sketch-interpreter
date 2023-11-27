#include "../../../../include/dlplan/core/elements/roles/argument.h"


namespace dlplan::core {
void ArgumentRole::compute_result(const State& state, RoleDenotation& result) const {
    const auto& argument_concents = state.get_state_extension()->get_role_argument_contents();
    if (m_pos < 0 || m_pos >= static_cast<int>(argument_concents.size())) {
        throw std::runtime_error("ArgumentRole::compute_result - register index out of bounds.");
    }
    result = argument_concents[m_pos];
}

RoleDenotation ArgumentRole::evaluate_impl(const State& state, DenotationsCaches&) const {
    RoleDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(
        state,
        denotation);
    return denotation;
}

RoleDenotations ArgumentRole::evaluate_impl(const States& states, DenotationsCaches& caches) const {
    RoleDenotations denotations;
    denotations.reserve(states.size());
    for (size_t i = 0; i < states.size(); ++i) {
        RoleDenotation denotation(states[i].get_instance_info()->get_objects().size());
        compute_result(
            states[i],
            denotation);
        denotations.push_back(caches.data.insert_unique<RoleDenotation>(std::move(denotation)));
    }
    return denotations;
}

ArgumentRole::ArgumentRole(ElementIndex index, std::shared_ptr<VocabularyInfo> vocabulary_info, int pos)
: Role(index, vocabulary_info, false), m_pos(pos) {
}

RoleDenotation ArgumentRole::evaluate(const State& state) const {
    RoleDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(state, denotation);
    return denotation;
}

bool ArgumentRole::are_equal_impl(const Role& other) const {
    if (typeid(*this) == typeid(other)) {
        const auto& other_derived = static_cast<const ArgumentRole&>(other);
        return m_is_static == other_derived.m_is_static
            && m_pos == other_derived.m_pos;
    }
    return false;
}

size_t ArgumentRole::hash_impl() const {
    return hash_combine(m_is_static, m_pos);
}

int ArgumentRole::compute_complexity_impl() const {
    return 1;
}

void ArgumentRole::str_impl(std::stringstream& out) const {
    out << "r_argument" << "(" << std::to_string(m_pos) << ")";
}

int ArgumentRole::compute_evaluate_time_score_impl() const {
    return SCORE_QUADRATIC;
}

}


namespace std {
    bool less<std::shared_ptr<const dlplan::core::ArgumentRole>>::operator()(
        const std::shared_ptr<const dlplan::core::ArgumentRole>& left_role,
        const std::shared_ptr<const dlplan::core::ArgumentRole>& right_role) const {
        return *left_role < *right_role;
    }

    std::size_t hash<dlplan::core::ArgumentRole>::operator()(const dlplan::core::ArgumentRole& role_) const {
        return role_.hash();
    }
}