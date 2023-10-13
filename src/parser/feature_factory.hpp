#ifndef SRC_PARSER_FEATURE_FACTORY_HPP_
#define SRC_PARSER_FEATURE_FACTORY_HPP_

#include <unordered_map>

#include "../extended_sketch/declarations.hpp"


namespace sketches::extended_sketch {

/// @brief Provides functionality for controlled creation and access of Booleans.
class BooleanFactory {
private:
    std::shared_ptr<dlplan::core::SyntacticElementFactory> m_factory;

    BooleanMap m_key_to_boolean;

public:
    explicit BooleanFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory);

    Boolean make_boolean(const std::string& key, const std::string& repr);

    Boolean get_boolean(const std::string& key) const;
};


/// @brief Provides functionality for controlled creation and access of Numericals.
class NumericalFactory {
private:
    std::shared_ptr<dlplan::core::SyntacticElementFactory> m_factory;

    NumericalMap m_key_to_numerical;

public:
    explicit NumericalFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory);

    Numerical make_numerical(const std::string& key, const std::string& repr);

    Numerical get_numerical(const std::string& key) const;
};


/// @brief Provides functionality for controlled creation and access of Booleans.
class ConceptFactory {
private:
    std::shared_ptr<dlplan::core::SyntacticElementFactory> m_factory;

    ConceptMap m_key_to_concept;

public:
    explicit ConceptFactory(std::shared_ptr<dlplan::core::SyntacticElementFactory> factory);

    Concept make_concept(const std::string& key, const std::string& repr);

    Concept get_concept(const std::string& key) const;
};

}


#endif
