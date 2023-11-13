#include "effect.h"

#include "../core/elements/utils.h"
#include "../../include/dlplan/core.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

using namespace dlplan;


namespace dlplan::policy {

BooleanEffect::BooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index)
    : BaseEffect(index), m_boolean(boolean) { }

int BooleanEffect::compute_evaluate_time_score() const {
    return m_boolean->compute_evaluate_time_score();
}

std::shared_ptr<const NamedBoolean> BooleanEffect::get_boolean() const {
    return m_boolean;
}

std::shared_ptr<const NamedNumerical> BooleanEffect::get_numerical() const {
    return nullptr;
}

std::shared_ptr<const NamedConcept> BooleanEffect::get_concept() const {
    return nullptr;
}


NumericalEffect::NumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index)
    : BaseEffect(index), m_numerical(numerical) { }

int NumericalEffect::compute_evaluate_time_score() const {
    return m_numerical->compute_evaluate_time_score();
}

std::shared_ptr<const NamedBoolean> NumericalEffect::get_boolean() const {
    return nullptr;
}

std::shared_ptr<const NamedNumerical> NumericalEffect::get_numerical() const {
    return m_numerical;
}

std::shared_ptr<const NamedConcept> NumericalEffect::get_concept() const {
    return nullptr;
}


ConceptEffect::ConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index)
    : BaseEffect(index), m_concept(concept) { }

int ConceptEffect::compute_evaluate_time_score() const {
    return m_concept->compute_evaluate_time_score();
}

std::shared_ptr<const NamedBoolean> ConceptEffect::get_boolean() const {
    return nullptr;
}

std::shared_ptr<const NamedNumerical> ConceptEffect::get_numerical() const {
    return nullptr;
}

std::shared_ptr<const NamedConcept> ConceptEffect::get_concept() const {
    return m_concept;
}


PositiveBooleanEffect::PositiveBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index)
    : BooleanEffect(boolean, index) {}

bool PositiveBooleanEffect::evaluate(const core::State&, const core::State& target_state) const {
    return m_boolean->get_boolean()->evaluate(target_state);
}

bool PositiveBooleanEffect::evaluate(const core::State&, const core::State& target_state, core::DenotationsCaches& caches) const {
    return m_boolean->get_boolean()->evaluate(target_state, caches);
}

std::string PositiveBooleanEffect::compute_repr() const{
    return "(:e_b_pos \"" + m_boolean->get_boolean()->compute_repr() + "\")";
}

std::string PositiveBooleanEffect::str() const {
    return "(:e_b_pos " + m_boolean->get_key() + ")";
}


NegativeBooleanEffect::NegativeBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index)
    : BooleanEffect(boolean, index) {}

bool NegativeBooleanEffect::evaluate(const core::State&, const core::State& target_state) const {
    return !m_boolean->get_boolean()->evaluate(target_state);
}

bool NegativeBooleanEffect::evaluate(const core::State&, const core::State& target_state, core::DenotationsCaches& caches) const {
    return !m_boolean->get_boolean()->evaluate(target_state, caches);
}

std::string NegativeBooleanEffect::compute_repr() const{
    return "(:e_b_neg \"" + m_boolean->get_boolean()->compute_repr() + "\")";
}

std::string NegativeBooleanEffect::str() const {
    return "(:e_b_neg " + m_boolean->get_key() + ")";
}


UnchangedBooleanEffect::UnchangedBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index)
    : BooleanEffect(boolean, index) {}

bool UnchangedBooleanEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_boolean->get_boolean()->evaluate(source_state) == m_boolean->get_boolean()->evaluate(target_state);
}

bool UnchangedBooleanEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    return m_boolean->get_boolean()->evaluate(source_state, caches) == m_boolean->get_boolean()->evaluate(target_state, caches);
}

std::string UnchangedBooleanEffect::compute_repr() const{
    return "(:e_b_bot \"" + m_boolean->get_boolean()->compute_repr() + "\")";
}

std::string UnchangedBooleanEffect::str() const {
    return "(:e_b_bot " + m_boolean->get_key() + ")";
}


IncrementNumericalEffect::IncrementNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index)
    : NumericalEffect(numerical, index) {}

bool IncrementNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_numerical->get_numerical()->evaluate(source_state) < m_numerical->get_numerical()->evaluate(target_state);
}

bool IncrementNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_numerical->get_numerical()->evaluate(source_state, caches);
    int target_eval = m_numerical->get_numerical()->evaluate(target_state, caches);
    if (source_eval == INF) return false;
    if (target_eval == INF) return false;
    return source_eval < target_eval;
}

std::string IncrementNumericalEffect::compute_repr() const{
    return "(:e_n_inc \"" + m_numerical->get_numerical()->compute_repr() + "\")";
}

std::string IncrementNumericalEffect::str() const {
    return "(:e_n_inc " + m_numerical->get_key() + ")";
}


DecrementNumericalEffect::DecrementNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index)
    : NumericalEffect(numerical, index) {}

bool DecrementNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_numerical->get_numerical()->evaluate(source_state) > m_numerical->get_numerical()->evaluate(target_state);
}

bool DecrementNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_numerical->get_numerical()->evaluate(source_state, caches);
    int target_eval = m_numerical->get_numerical()->evaluate(target_state, caches);
    if (source_eval == INF) return false;
    if (target_eval == INF) return false;
    return source_eval > target_eval;
}

std::string DecrementNumericalEffect::compute_repr() const{
    return "(:e_n_dec \"" + m_numerical->get_numerical()->compute_repr() + "\")";
}

std::string DecrementNumericalEffect::str() const {
    return "(:e_n_dec " + m_numerical->get_key() + ")";
}


UnchangedNumericalEffect::UnchangedNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index)
    : NumericalEffect(numerical, index) {}

bool UnchangedNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_numerical->get_numerical()->evaluate(source_state) == m_numerical->get_numerical()->evaluate(target_state);
}

bool UnchangedNumericalEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_numerical->get_numerical()->evaluate(source_state, caches);
    int target_eval = m_numerical->get_numerical()->evaluate(target_state, caches);
    return source_eval == target_eval;
}

std::string UnchangedNumericalEffect::compute_repr() const{
    return "(:e_n_bot \"" + m_numerical->get_numerical()->compute_repr() + "\")";
}

std::string UnchangedNumericalEffect::str() const {
    return "(:e_n_bot " + m_numerical->get_key() + ")";
}


IncrementConceptEffect::IncrementConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index)
    : ConceptEffect(concept, index) {}

bool IncrementConceptEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_concept->get_concept()->evaluate(source_state).size() < m_concept->get_concept()->evaluate(target_state).size();
}

bool IncrementConceptEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_concept->get_concept()->evaluate(source_state, caches)->size();
    int target_eval = m_concept->get_concept()->evaluate(target_state, caches)->size();
    if (source_eval == INF) return false;
    if (target_eval == INF) return false;
    return source_eval < target_eval;
}

std::string IncrementConceptEffect::compute_repr() const{
    return "(:e_c_inc \"" + m_concept->get_concept()->compute_repr() + "\")";
}

std::string IncrementConceptEffect::str() const {
    return "(:e_c_inc " + m_concept->get_key() + ")";
}


DecrementConceptEffect::DecrementConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index)
    : ConceptEffect(concept, index) {}

bool DecrementConceptEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_concept->get_concept()->evaluate(source_state).size() > m_concept->get_concept()->evaluate(target_state).size();
}

bool DecrementConceptEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_concept->get_concept()->evaluate(source_state, caches)->size();
    int target_eval = m_concept->get_concept()->evaluate(target_state, caches)->size();
    if (source_eval == INF) return false;
    if (target_eval == INF) return false;
    return source_eval > target_eval;
}

std::string DecrementConceptEffect::compute_repr() const{
    return "(:e_c_dec \"" + m_concept->get_concept()->compute_repr() + "\")";
}

std::string DecrementConceptEffect::str() const {
    return "(:e_c_dec " + m_concept->get_key() + ")";
}


UnchangedConceptEffect::UnchangedConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index)
    : ConceptEffect(concept, index) {}

bool UnchangedConceptEffect::evaluate(const core::State& source_state, const core::State& target_state) const {
    return m_concept->get_concept()->evaluate(source_state).size() == m_concept->get_concept()->evaluate(target_state).size();
}

bool UnchangedConceptEffect::evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const {
    int source_eval = m_concept->get_concept()->evaluate(source_state, caches)->size();
    int target_eval = m_concept->get_concept()->evaluate(target_state, caches)->size();
    return source_eval == target_eval;
}

std::string UnchangedConceptEffect::compute_repr() const{
    return "(:e_c_bot \"" + m_concept->get_concept()->compute_repr() + "\")";
}

std::string UnchangedConceptEffect::str() const {
    return "(:e_c_bot " + m_concept->get_key() + ")";
}

}

namespace boost::serialization {
template<typename Archive>
void serialize( Archive& /* ar */ , dlplan::policy::BooleanEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BaseEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& /* ar */ , const dlplan::policy::BooleanEffect* /* t */ , const unsigned int /* version */ )
{
}

template<class Archive>
void load_construct_data(Archive& /* ar */ , dlplan::policy::BooleanEffect* /* t */ , const unsigned int /* version */ )
{
}

template<typename Archive>
void serialize( Archive& /* ar */ , dlplan::policy::NumericalEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BaseEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& /* ar */ , const dlplan::policy::NumericalEffect* /* t */ , const unsigned int /* version */ )
{
}

template<class Archive>
void load_construct_data(Archive& /* ar */ , dlplan::policy::NumericalEffect* /* t */ , const unsigned int /* version */ )
{
}

template<typename Archive>
void serialize( Archive& /* ar */ , dlplan::policy::ConceptEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BaseEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& /* ar */ , const dlplan::policy::ConceptEffect* /* t */ , const unsigned int /* version */ )
{
}

template<class Archive>
void load_construct_data(Archive& /* ar */ , dlplan::policy::ConceptEffect* /* t */ , const unsigned int /* version */ )
{
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::PositiveBooleanEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BooleanEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::PositiveBooleanEffect* t, const unsigned int /* version */ )
{
    ar << t->m_boolean;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::PositiveBooleanEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedBoolean> boolean;
    dlplan::policy::EffectIndex index;
    ar >> boolean;
    ar >> index;
    ::new(t)dlplan::policy::PositiveBooleanEffect(boolean, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::NegativeBooleanEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BooleanEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::NegativeBooleanEffect* t, const unsigned int /* version */ )
{
    ar << t->m_boolean;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::NegativeBooleanEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedBoolean> boolean;
    dlplan::policy::EffectIndex index;
    ar >> boolean;
    ar >> index;
    ::new(t)dlplan::policy::NegativeBooleanEffect(boolean, index);
}

template<typename Archive>
void serialize( Archive& /* ar */ , dlplan::policy::UnchangedBooleanEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::BooleanEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::UnchangedBooleanEffect* t, const unsigned int /* version */ )
{
    ar << t->m_boolean;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::UnchangedBooleanEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedBoolean> boolean;
    dlplan::policy::EffectIndex index;
    ar >> boolean;
    ar >> index;
    ::new(t)dlplan::policy::UnchangedBooleanEffect(boolean, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::IncrementNumericalEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::NumericalEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::IncrementNumericalEffect* t, const unsigned int /* version */ )
{
    ar << t->m_numerical;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::IncrementNumericalEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedNumerical> numerical;
    dlplan::policy::EffectIndex index;
    ar >> numerical;
    ar >> index;
    ::new(t)dlplan::policy::IncrementNumericalEffect(numerical, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::DecrementNumericalEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::NumericalEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::DecrementNumericalEffect* t, const unsigned int /* version */ )
{
    ar << t->m_numerical;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::DecrementNumericalEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedNumerical> numerical;
    dlplan::policy::EffectIndex index;
    ar >> numerical;
    ar >> index;
    ::new(t)dlplan::policy::DecrementNumericalEffect(numerical, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::UnchangedNumericalEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::NumericalEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::UnchangedNumericalEffect* t, const unsigned int /* version */ )
{
    ar << t->m_numerical;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::UnchangedNumericalEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedNumerical> numerical;
    dlplan::policy::EffectIndex index;
    ar >> numerical;
    ar >> index;
    ::new(t)dlplan::policy::UnchangedNumericalEffect(numerical, index);
}



template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::IncrementConceptEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::ConceptEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::IncrementConceptEffect* t, const unsigned int /* version */ )
{
    ar << t->m_concept;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::IncrementConceptEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedConcept> concept;
    dlplan::policy::EffectIndex index;
    ar >> concept;
    ar >> index;
    ::new(t)dlplan::policy::IncrementConceptEffect(concept, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::DecrementConceptEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::ConceptEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::DecrementConceptEffect* t, const unsigned int /* version */ )
{
    ar << t->m_concept;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::DecrementConceptEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedConcept> concept;
    dlplan::policy::EffectIndex index;
    ar >> concept;
    ar >> index;
    ::new(t)dlplan::policy::DecrementConceptEffect(concept, index);
}

template<typename Archive>
void serialize(Archive& /* ar */ , dlplan::policy::UnchangedConceptEffect& t, const unsigned int /* version */ )
{
    boost::serialization::base_object<dlplan::policy::ConceptEffect>(t);
}

template<class Archive>
void save_construct_data(Archive& ar, const dlplan::policy::UnchangedConceptEffect* t, const unsigned int /* version */ )
{
    ar << t->m_concept;
    ar << t->m_index;
}

template<class Archive>
void load_construct_data(Archive& ar, dlplan::policy::UnchangedConceptEffect* t, const unsigned int /* version */ )
{
    std::shared_ptr<const dlplan::policy::NamedConcept> concept;
    dlplan::policy::EffectIndex index;
    ar >> concept;
    ar >> index;
    ::new(t)dlplan::policy::UnchangedConceptEffect(concept, index);
}

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::BooleanEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::BooleanEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::BooleanEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::BooleanEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::PositiveBooleanEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::PositiveBooleanEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::PositiveBooleanEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::PositiveBooleanEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::NegativeBooleanEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::NegativeBooleanEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::NegativeBooleanEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::NegativeBooleanEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedBooleanEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::UnchangedBooleanEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::UnchangedBooleanEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedBooleanEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::NumericalEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::NumericalEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::NumericalEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::NumericalEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::IncrementNumericalEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::IncrementNumericalEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::IncrementNumericalEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::IncrementNumericalEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::DecrementNumericalEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::DecrementNumericalEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::DecrementNumericalEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::DecrementNumericalEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedNumericalEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::UnchangedNumericalEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::UnchangedNumericalEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedNumericalEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::ConceptEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::ConceptEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::ConceptEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::ConceptEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::IncrementConceptEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::IncrementConceptEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::IncrementConceptEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::IncrementConceptEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::DecrementConceptEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::DecrementConceptEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::DecrementConceptEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::DecrementConceptEffect* t, const unsigned int version);

template void serialize(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedConceptEffect& t, const unsigned int version);
template void serialize(boost::archive::text_oarchive& ar,
    dlplan::policy::UnchangedConceptEffect& t, const unsigned int version);
template void save_construct_data(boost::archive::text_oarchive& ar,
    const dlplan::policy::UnchangedConceptEffect* t, const unsigned int version);
template void load_construct_data(boost::archive::text_iarchive& ar,
    dlplan::policy::UnchangedConceptEffect* t, const unsigned int version);
}

BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::PositiveBooleanEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::NegativeBooleanEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::UnchangedBooleanEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::IncrementNumericalEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::DecrementNumericalEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::UnchangedNumericalEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::IncrementConceptEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::DecrementConceptEffect)
BOOST_CLASS_EXPORT_IMPLEMENT(dlplan::policy::UnchangedConceptEffect)
