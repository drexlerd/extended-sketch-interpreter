#ifndef SRC_EXTENDED_SKETCH_FEATURES_HPP_
#define SRC_EXTENDED_SKETCH_FEATURES_HPP_

#include <string>
#include <memory>

#include "../external/dlplan/include/dlplan/core.h"


namespace sketches::extended_sketch {

class FeatureImpl {
protected:
    std::string m_key;

public:
    explicit FeatureImpl(const std::string& key);
    virtual ~FeatureImpl();

    const std::string& get_key() const;
};


class BooleanImpl : public FeatureImpl {
protected:
    std::shared_ptr<const dlplan::core::Boolean> m_boolean;

public:
    BooleanImpl(
        const std::string& key,
        const std::shared_ptr<const dlplan::core::Boolean>& boolean);
    ~BooleanImpl() override;

    std::shared_ptr<const dlplan::core::Boolean> get_boolean() const;
};

extern std::shared_ptr<BooleanImpl> create_boolean(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Boolean>& boolean);


class NumericalImpl : public FeatureImpl {
protected:
    std::shared_ptr<const dlplan::core::Numerical> m_numerical;

public:
    NumericalImpl(
        const std::string& key,
        const std::shared_ptr<const dlplan::core::Numerical>& numerical);
    ~NumericalImpl() override;

    std::shared_ptr<const dlplan::core::Numerical> get_numerical() const;
};

extern std::shared_ptr<NumericalImpl> create_numerical(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Numerical>& numerical);


class ConceptImpl : public FeatureImpl {
protected:
    std::shared_ptr<const dlplan::core::Concept> m_concept;

public:
    ConceptImpl(
        const std::string& key,
        const std::shared_ptr<const dlplan::core::Concept>& concept);
    ~ConceptImpl() override;

    std::shared_ptr<const dlplan::core::Concept> get_concept() const;
};

extern std::shared_ptr<ConceptImpl> create_concept(
    const std::string& key,
    const std::shared_ptr<const dlplan::core::Concept>& concept);

}


#endif
