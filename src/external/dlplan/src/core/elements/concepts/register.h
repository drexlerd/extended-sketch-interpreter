#ifndef DLPLAN_SRC_CORE_ELEMENTS_CONCEPTS_REGISTER_H_
#define DLPLAN_SRC_CORE_ELEMENTS_CONCEPTS_REGISTER_H_

#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "../utils.h"
#include "../../parser/expressions/concepts/register.h"
#include "../../../utils/collections.h"
#include "../../../../include/dlplan/core.h"

using namespace std::string_literals;


namespace dlplan::core {
class RegisterConcept;
}


namespace boost::serialization {
    template<typename Archive>
    void serialize(Archive& ar, dlplan::core::RegisterConcept& concept, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::core::RegisterConcept* concept, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::core::RegisterConcept* concept, const unsigned int version);
}


namespace dlplan::core {
class RegisterConcept : public Concept {
private:
    void compute_result(const State& state, ConceptDenotation& result) const {
    }

    ConceptDenotation evaluate_impl(const State& state, DenotationsCaches&) const override {
        ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
        compute_result(
            state,
            denotation);
        return denotation;
    }

    ConceptDenotations evaluate_impl(const States& states, DenotationsCaches& caches) const override {
        ConceptDenotations denotations;
        denotations.reserve(states.size());
        for (size_t i = 0; i < states.size(); ++i) {
            ConceptDenotation denotation(states[i].get_instance_info()->get_objects().size());
            compute_result(
                states[i],
                denotation);
            denotations.push_back(caches.concept_denotation_cache.insert_denotation(std::move(denotation)));
        }
        return denotations;
    }

    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, RegisterConcept& concept, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const RegisterConcept* concept, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, RegisterConcept* concept, const unsigned int version);

protected:
    const Register m_register;

public:
    RegisterConcept(std::shared_ptr<VocabularyInfo> vocabulary_info, ElementIndex index, const Register& reg)
    : Concept(vocabulary_info, index, false), m_register(reg) {  }

    ConceptDenotation evaluate(const State& state) const override {
        ConceptDenotation denotation(state.get_instance_info()->get_objects().size());
        compute_result(state, denotation);
        return denotation;
    }

    int compute_complexity() const override {
        return 1;
    }

    void compute_repr(std::stringstream& out) const override {
        out << parser::RegisterConcept::get_name() << "(" << m_register.get_index() << ")";
    }

    int compute_evaluate_time_score() const override {
        return SCORE_CONSTANT;
    }
};

}



namespace boost::serialization {
template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::core::RegisterConcept& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::core::Concept>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::core::RegisterConcept* t, const unsigned int /* version */ )
{
    ar << t->m_vocabulary_info;
    ar << t->m_index;
    ar << &t->m_register;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::core::RegisterConcept* t, const unsigned int /* version */ )
{
    std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary;
    int index;
    dlplan::core::Register* reg;
    ar >> vocabulary;
    ar >> index;
    ar >> reg;
    ::new(t)dlplan::core::RegisterConcept(vocabulary, index, *reg);
    delete reg;
}

}

BOOST_CLASS_EXPORT_GUID(dlplan::core::RegisterConcept, "dlplan::core::RegisterConcept")

#endif
