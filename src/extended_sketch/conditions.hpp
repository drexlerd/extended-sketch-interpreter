#ifndef SRC_EXTENDED_SKETCH_CONDITIONS_HPP_
#define SRC_EXTENDED_SKETCH_CONDITIONS_HPP_

#include "declarations.hpp"


namespace sketches::extended_sketch {
class ConditionImpl {
protected:
public:
    virtual ~ConditionImpl();
};


class BooleanConditionImpl {
protected:
    Boolean m_boolean;

public:
    BooleanConditionImpl(const Boolean& boolean);
};


class NumericalConditionImpl {
protected:
    Numerical m_numerical;

public:
    NumericalConditionImpl(const Numerical& numerical);
};


class PositiveBooleanConditionImpl : public BooleanConditionImpl {
protected:
};

class NegativeBooleanConditionImpl : public BooleanConditionImpl {
protected:
};

class EqualNumericalConditionImpl : public NumericalConditionImpl {
protected:
};

class GreaterNumericalConditionImpl : public NumericalConditionImpl {
protected:
};

}

#endif
