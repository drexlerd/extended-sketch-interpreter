#include "features.hpp"


namespace sketches::extended_sketch {

FeatureImpl::FeatureImpl(const std::string& key)
    : m_key(key) { }

FeatureImpl::~FeatureImpl() = default;

const std::string& FeatureImpl::get_key() const {
    return m_key;
}


BooleanImpl::BooleanImpl(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Boolean>& boolean)
    : FeatureImpl(key), m_boolean(boolean) { }

BooleanImpl::~BooleanImpl() = default;

std::shared_ptr<const dlplan::core::Boolean> BooleanImpl::get_boolean() const {
    return m_boolean;
}

std::shared_ptr<BooleanImpl> create_boolean(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Boolean>& boolean) {
    return std::make_shared<BooleanImpl>(key, boolean);
}


NumericalImpl::NumericalImpl(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Numerical>& numerical)
    : FeatureImpl(key), m_numerical(numerical) { }

NumericalImpl::~NumericalImpl() = default;

std::shared_ptr<const dlplan::core::Numerical> NumericalImpl::get_numerical() const {
    return m_numerical;
}

std::shared_ptr<NumericalImpl> create_numerical(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Numerical>& numerical) {
    return std::make_shared<NumericalImpl>(key, numerical);
}


ConceptImpl::ConceptImpl(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Concept>& concept)
    : FeatureImpl(key), m_concept(concept) { }

ConceptImpl::~ConceptImpl() = default;

std::shared_ptr<const dlplan::core::Concept> ConceptImpl::get_concept() const {
    return m_concept;
}

std::shared_ptr<ConceptImpl> create_concept(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Concept>& concept) {
    return std::make_shared<ConceptImpl>(key, concept);
}


}