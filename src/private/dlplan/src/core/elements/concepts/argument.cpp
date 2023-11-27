#include "../../../../include/dlplan/core/elements/concepts/argument.h"


namespace dlplan::core {
void ArgumentConcept::compute_result(const State& state, ConceptDenotation& result) const {
    const auto& argument_concents = state.get_argument_contents();
    if (m_pos < 0 || m_pos >= static_cast<int>(argument_concents.size())) {
        throw std::runtime_error("ArgumentConcept::compute_result - register index out of bounds.");
    }
    result = argument_concents[m_pos];
}

ConceptDenotation ArgumentConcept::evaluate_impl(const State& state, DenotationsCaches&) const {
    ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(
        state,
        denotation);
    return denotation;
}

ConceptDenotations ArgumentConcept::evaluate_impl(const States& states, DenotationsCaches& caches) const {
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

ArgumentConcept::ArgumentConcept(ElementIndex index, std::shared_ptr<VocabularyInfo> vocabulary_info, int pos)
: Concept(index, vocabulary_info, false), m_pos(pos) {
}

ConceptDenotation ArgumentConcept::evaluate(const State& state) const {
    ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
    compute_result(state, denotation);
    return denotation;
}

bool ArgumentConcept::are_equal_impl(const Concept& other) const {
    if (typeid(*this) == typeid(other)) {
        const auto& other_derived = static_cast<const ArgumentConcept&>(other);
        return m_is_static == other_derived.m_is_static
            && m_pos == other_derived.m_pos;
    }
    return false;
}

size_t ArgumentConcept::hash_impl() const {
    return hash_combine(m_is_static, m_pos);
}

int ArgumentConcept::compute_complexity_impl() const {
    return 1;
}

void ArgumentConcept::str_impl(std::stringstream& out) const {
    out << "c_argument" << "(" << std::to_string(m_pos) << ")";
}

int ArgumentConcept::compute_evaluate_time_score_impl() const {
    return SCORE_LINEAR;
}

}


namespace std {
    bool less<std::shared_ptr<const dlplan::core::ArgumentConcept>>::operator()(
        const std::shared_ptr<const dlplan::core::ArgumentConcept>& left_concept,
        const std::shared_ptr<const dlplan::core::ArgumentConcept>& right_concept) const {
        return *left_concept < *right_concept;
    }

    std::size_t hash<dlplan::core::ArgumentConcept>::operator()(const dlplan::core::ArgumentConcept& concept_) const {
        return concept_.hash();
    }
}