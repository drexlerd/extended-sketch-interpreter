#include "../../../../include/dlplan/core/elements/concepts/register.h"


namespace dlplan::core {

void RegisterConcept::compute_result(const State& state, ConceptDenotation& result) const {
    const auto& register_content = state.get_state_extension()->get_register_contents();
    if (m_pos < 0 || m_pos >= static_cast<int>(register_content.size())) {
        throw std::runtime_error("RegisterConcept::compute_result - register index out of bounds.");
    }
    result.insert(register_content[m_pos]);
}

ConceptDenotation RegisterConcept::evaluate_impl(const State& state, DenotationsCaches&) const {
    ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(
        state,
        denotation);
    return denotation;
}

ConceptDenotations RegisterConcept::evaluate_impl(const States& states, DenotationsCaches& caches) const {
    ConceptDenotations denotations;
    denotations.reserve(states.size());
    for (size_t i = 0; i < states.size(); ++i) {
        ConceptDenotation denotation(states[i].get_instance_info()->get_objects().size());
        compute_result(
            states[i],
            denotation);
        denotations.push_back(caches.data.insert_unique<ConceptDenotation>(std::move(denotation)));
    }
    return denotations;
}

RegisterConcept::RegisterConcept(ElementIndex index, std::shared_ptr<VocabularyInfo> vocabulary_info, int pos)
: Concept(index, vocabulary_info, false), m_pos(pos) {
}


ConceptDenotation RegisterConcept::evaluate(const State& state) const {
    ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(state, denotation);
    return denotation;
}

bool RegisterConcept::are_equal_impl(const Concept& other) const {
    if (typeid(*this) == typeid(other)) {
        const auto& other_derived = static_cast<const RegisterConcept&>(other);
        return m_is_static == other_derived.m_is_static
            && m_pos == other_derived.m_pos;
    }
    return false;
}

size_t RegisterConcept::hash_impl() const {
    return hash_combine(m_is_static, m_pos);
}

int RegisterConcept::compute_complexity_impl() const {
    return 1;
}

void RegisterConcept::str_impl(std::stringstream& out) const {
    out << "c_register" << "(" << std::to_string(m_pos) << ")";
}

int RegisterConcept::compute_evaluate_time_score_impl() const {
    return SCORE_LINEAR;
}
}


namespace std {
    bool less<std::shared_ptr<const dlplan::core::RegisterConcept>>::operator()(
        const std::shared_ptr<const dlplan::core::RegisterConcept>& left_concept,
        const std::shared_ptr<const dlplan::core::RegisterConcept>& right_concept) const {
        return *left_concept < *right_concept;
    }

    std::size_t hash<dlplan::core::RegisterConcept>::operator()(const dlplan::core::RegisterConcept& concept_) const {
        return concept_.hash();
    }
}
