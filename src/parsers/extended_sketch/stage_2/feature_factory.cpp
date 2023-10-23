#include "feature_factory.hpp"


namespace sketches::parsers::extended_sketch::stage_2 {

BooleanFactory::BooleanFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory)
    : m_policy_factory(policy_factory) { }

Boolean BooleanFactory::make_boolean(const std::string& key, const std::string& repr) {
    return m_key_to_boolean.emplace(key, m_policy_factory->make_boolean(key, m_policy_factory->get_element_factory()->parse_boolean(repr))).first->second;
}

Boolean BooleanFactory::get_boolean(const std::string& key) const {
    auto find = m_key_to_boolean.find(key);
    if (find == m_key_to_boolean.end()) {
        return nullptr;
    }
    return find->second;
}


NumericalFactory::NumericalFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory)
    : m_policy_factory(policy_factory) { }

Numerical NumericalFactory::make_numerical(const std::string& key, const std::string& repr) {
    return m_key_to_numerical.emplace(key, m_policy_factory->make_numerical(key, m_policy_factory->get_element_factory()->parse_numerical(repr))).first->second;
}

Numerical NumericalFactory::get_numerical(const std::string& key) const {
    auto find = m_key_to_numerical.find(key);
    if (find == m_key_to_numerical.end()) {
        return nullptr;
    }
    return find->second;
}


ConceptFactory::ConceptFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory)
    : m_policy_factory(policy_factory) { }

Concept ConceptFactory::make_concept(const std::string& key, const std::string& repr) {
    return m_key_to_concept.emplace(key, m_policy_factory->make_concept(key, m_policy_factory->get_element_factory()->parse_concept(repr))).first->second;
}

Concept ConceptFactory::get_concept(const std::string& key) const {
    auto find = m_key_to_concept.find(key);
    if (find == m_key_to_concept.end()) {
        return nullptr;
    }
    return find->second;
}

}