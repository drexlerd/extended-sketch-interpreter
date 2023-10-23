#ifndef SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_FEATURE_FACTORY_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_STAGE_2_FEATURE_FACTORY_HPP_

#include <unordered_map>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"

#include "src/extended_sketch/declarations.hpp"

using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch::stage_2 {

/// @brief Provides functionality for controlled creation and access of Booleans.
class BooleanFactory {
private:
    std::shared_ptr<dlplan::policy::PolicyFactory> m_policy_factory;

    BooleanMap m_key_to_boolean;

public:
    explicit BooleanFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory);

    Boolean make_boolean(const std::string& key, const std::string& repr);

    Boolean get_boolean(const std::string& key) const;
};


/// @brief Provides functionality for controlled creation and access of Numericals.
class NumericalFactory {
private:
    std::shared_ptr<dlplan::policy::PolicyFactory> m_policy_factory;

    NumericalMap m_key_to_numerical;

public:
    explicit NumericalFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory);

    Numerical make_numerical(const std::string& key, const std::string& repr);

    Numerical get_numerical(const std::string& key) const;
};


/// @brief Provides functionality for controlled creation and access of Booleans.
class ConceptFactory {
private:
    std::shared_ptr<dlplan::policy::PolicyFactory> m_policy_factory;

    ConceptMap m_key_to_concept;

public:
    explicit ConceptFactory(std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory);

    Concept make_concept(const std::string& key, const std::string& repr);

    Concept get_concept(const std::string& key) const;
};

}


#endif
