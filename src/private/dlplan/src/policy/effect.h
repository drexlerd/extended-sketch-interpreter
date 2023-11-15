#ifndef DLPLAN_SRC_POLICY_EFFECT_H_
#define DLPLAN_SRC_POLICY_EFFECT_H_

#include "../../include/dlplan/policy.h"

#include <boost/serialization/export.hpp>

#include <string>
#include <memory>


namespace dlplan::policy {
class BooleanEffect;
class NumericalEffect;
class ConceptEffect;
class PositiveBooleanEffect;
class NegativeBooleanEffect;
class UnchangedBooleanEffect;
class IncrementNumericalEffect;
class DecrementNumericalEffect;
class UnchangedNumericalEffect;
class GreaterNumericalEffect;
class EqualNumericalEffect;
class IncrementConceptEffect;
class DecrementConceptEffect;
class UnchangedConceptEffect;
class GreaterConceptEffect;
class EqualConceptEffect;
}


namespace boost::serialization {
    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::BooleanEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::BooleanEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::BooleanEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::NumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::NumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::NumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::ConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::ConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::ConceptEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::PositiveBooleanEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::PositiveBooleanEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::PositiveBooleanEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::NegativeBooleanEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::NegativeBooleanEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::NegativeBooleanEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::UnchangedBooleanEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::UnchangedBooleanEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::UnchangedBooleanEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::IncrementNumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::IncrementNumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::IncrementNumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::DecrementNumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::DecrementNumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::DecrementNumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::UnchangedNumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::UnchangedNumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::UnchangedNumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::GreaterNumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::GreaterNumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::GreaterNumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::EqualNumericalEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::EqualNumericalEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::EqualNumericalEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::IncrementConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::IncrementConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::IncrementConceptEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::DecrementConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::DecrementConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::DecrementConceptEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::UnchangedConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::UnchangedConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::UnchangedConceptEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::GreaterConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::GreaterConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::GreaterConceptEffect* t, const unsigned int version);

    template <typename Archive>
    void serialize(Archive& ar, dlplan::policy::EqualConceptEffect& effect, const unsigned int version);
    template<class Archive>
    void save_construct_data(Archive& ar, const dlplan::policy::EqualConceptEffect* t, const unsigned int version);
    template<class Archive>
    void load_construct_data(Archive& ar, dlplan::policy::EqualConceptEffect* t, const unsigned int version);
}


namespace dlplan::policy {
class BooleanEffect : public BaseEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, BooleanEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const BooleanEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, BooleanEffect* t, const unsigned int version);

protected:
    std::shared_ptr<const NamedBoolean> m_boolean;

protected:
    BooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index);

    int compute_evaluate_time_score() const override;

    std::shared_ptr<const NamedBoolean> get_boolean() const override;
    std::shared_ptr<const NamedNumerical> get_numerical() const override;
    std::shared_ptr<const NamedConcept> get_concept() const override;
};


class NumericalEffect : public BaseEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, NumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const NumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, NumericalEffect* t, const unsigned int version);

protected:
    std::shared_ptr<const NamedNumerical> m_numerical;

protected:
    NumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    int compute_evaluate_time_score() const override;

    std::shared_ptr<const NamedBoolean> get_boolean() const override;
    std::shared_ptr<const NamedNumerical> get_numerical() const override;
    std::shared_ptr<const NamedConcept> get_concept() const override;
};


class ConceptEffect : public BaseEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, ConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const ConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, ConceptEffect* t, const unsigned int version);

protected:
    std::shared_ptr<const NamedConcept> m_concept;

protected:
    ConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    int compute_evaluate_time_score() const override;

    std::shared_ptr<const NamedBoolean> get_boolean() const override;
    std::shared_ptr<const NamedNumerical> get_numerical() const override;
    std::shared_ptr<const NamedConcept> get_concept() const override;
};


class PositiveBooleanEffect : public BooleanEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, PositiveBooleanEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const PositiveBooleanEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, PositiveBooleanEffect* t, const unsigned int version);

public:
    PositiveBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};


class NegativeBooleanEffect : public BooleanEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, NegativeBooleanEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const NegativeBooleanEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, NegativeBooleanEffect* t, const unsigned int version);

public:
    NegativeBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class UnchangedBooleanEffect : public BooleanEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, UnchangedBooleanEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const UnchangedBooleanEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, UnchangedBooleanEffect* t, const unsigned int version);

public:
    UnchangedBooleanEffect(std::shared_ptr<const NamedBoolean> boolean, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class IncrementNumericalEffect : public NumericalEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, IncrementNumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const IncrementNumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, IncrementNumericalEffect* t, const unsigned int version);

public:
    IncrementNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class DecrementNumericalEffect : public NumericalEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, DecrementNumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const DecrementNumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, DecrementNumericalEffect* t, const unsigned int version);

public:
    DecrementNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class UnchangedNumericalEffect : public NumericalEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, UnchangedNumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const UnchangedNumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, UnchangedNumericalEffect* t, const unsigned int version);

public:
    UnchangedNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class GreaterNumericalEffect : public NumericalEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, GreaterNumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const GreaterNumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, GreaterNumericalEffect* t, const unsigned int version);

public:
    GreaterNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class EqualNumericalEffect : public NumericalEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, EqualNumericalEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const EqualNumericalEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, EqualNumericalEffect* t, const unsigned int version);

public:
    EqualNumericalEffect(std::shared_ptr<const NamedNumerical> numerical, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};


class IncrementConceptEffect : public ConceptEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, IncrementConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const IncrementConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, IncrementConceptEffect* t, const unsigned int version);

public:
    IncrementConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class DecrementConceptEffect : public ConceptEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, DecrementConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const DecrementConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, DecrementConceptEffect* t, const unsigned int version);

public:
    DecrementConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class UnchangedConceptEffect : public ConceptEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, UnchangedConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const UnchangedConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, UnchangedConceptEffect* t, const unsigned int version);

public:
    UnchangedConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class GreaterConceptEffect : public ConceptEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, GreaterConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const GreaterConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, GreaterConceptEffect* t, const unsigned int version);

public:
    GreaterConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};

class EqualConceptEffect : public ConceptEffect {
private:
    template<typename Archive>
    friend void boost::serialization::serialize(Archive& ar, EqualConceptEffect& t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::save_construct_data(Archive& ar, const EqualConceptEffect* t, const unsigned int version);
    template<class Archive>
    friend void boost::serialization::load_construct_data(Archive& ar, EqualConceptEffect* t, const unsigned int version);

public:
    EqualConceptEffect(std::shared_ptr<const NamedConcept> concept, EffectIndex index);

    bool evaluate(const core::State& source_state, const core::State& target_state) const override;
    bool evaluate(const core::State& source_state, const core::State& target_state, core::DenotationsCaches& caches) const override;

    std::string compute_repr() const override;
    std::string str() const override;
};


}

BOOST_CLASS_EXPORT_KEY2(dlplan::policy::PositiveBooleanEffect, "dlplan::policy::PositiveBooleanEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::NegativeBooleanEffect, "dlplan::policy::NegativeBooleanEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::UnchangedBooleanEffect, "dlplan::policy::UnchangedBooleanEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::IncrementNumericalEffect, "dlplan::policy::IncrementNumericalEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::DecrementNumericalEffect, "dlplan::policy::DecrementNumericalEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::UnchangedNumericalEffect, "dlplan::policy::UnchangedNumericalEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::GreaterNumericalEffect, "dlplan::policy::GreaterNumericalEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::EqualNumericalEffect, "dlplan::policy::EqualNumericalEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::IncrementConceptEffect, "dlplan::policy::IncrementConceptEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::DecrementConceptEffect, "dlplan::policy::DecrementConceptEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::UnchangedConceptEffect, "dlplan::policy::UnchangedConceptEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::GreaterConceptEffect, "dlplan::policy::GreaterConceptEffect")
BOOST_CLASS_EXPORT_KEY2(dlplan::policy::EqualConceptEffect, "dlplan::policy::EqualConceptEffect")

#endif