#include "feature_factory.hpp"

#include "../extended_sketch/features.hpp"

namespace sketches::extended_sketch {

BooleanFactory::BooleanFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory)
    : m_factory(factory) { }

Boolean BooleanFactory::make_boolean(const std::string& key, const std::string& repr) {
    return m_key_to_boolean.emplace(key, create_boolean(key, m_factory->parse_boolean(repr))).first->second;
}

Boolean BooleanFactory::get_boolean(const std::string& key) const {
    auto find = m_key_to_boolean.find(key);
    if (find == m_key_to_boolean.end()) {
        throw std::runtime_error("BooleanFactory::get_boolean - no boolean exists for key: " + key);
    }
    return find->second;
}


NumericalFactory::NumericalFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory)
    : m_factory(factory) { }

Numerical NumericalFactory::make_numerical(const std::string& key, const std::string& repr) {
    return m_key_to_numerical.emplace(key, create_numerical(key, m_factory->parse_numerical(repr))).first->second;
}

Numerical NumericalFactory::get_numerical(const std::string& key) const {
    auto find = m_key_to_numerical.find(key);
    if (find == m_key_to_numerical.end()) {
        throw std::runtime_error("NumericalFactory::get_numerical - no numerical exists for key: " + key);
    }
    return find->second;
}


ConceptFactory::ConceptFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory)
    : m_factory(factory) { }

Concept ConceptFactory::make_concept(const std::string& key, const std::string& repr) {
    return m_key_to_concept.emplace(key, create_concept(key, m_factory->parse_concept(repr))).first->second;
}

Concept ConceptFactory::get_concept(const std::string& key) const {
    auto find = m_key_to_concept.find(key);
    if (find == m_key_to_concept.end()) {
        throw std::runtime_error("ConceptFactory::get_concept - no concept exists for key: " + key);
    }
    return find->second;
}

}