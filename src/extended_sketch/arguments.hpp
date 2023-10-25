#ifndef SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_
#define SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_

#include <string>
#include <variant>
#include <vector>


namespace sketches::extended_sketch {
struct ArgumentVariant;
using ArgumentVariantList = std::vector<ArgumentVariant>;

// Arguments are just types with a name to select objects from the current stack frame.
class Argument {
private:
    std::string m_key;

public:
    explicit Argument(const std::string& key);
    virtual ~Argument();

    const std::string& get_key() const;
};


class ArgumentRegister : public Argument {
public:
    ArgumentRegister(const std::string& key);
};


class ArgumentConcept : public Argument {
public:
    ArgumentConcept(const std::string& key);
};


struct ArgumentVariant {
    std::variant<ArgumentRegister, ArgumentConcept> argument;
};

}

#endif