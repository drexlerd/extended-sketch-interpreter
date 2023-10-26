#ifndef SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_
#define SRC_EXTENDED_SKETCH_ARGUMENTS_HPP_

#include <string>
#include <variant>
#include <vector>


namespace sketches::extended_sketch {
class BaseArgument;
class ArgumentRegister;
class ArgumentConcept;
using Argument = std::variant<BaseArgument, ArgumentRegister, ArgumentConcept>;
using ArgumentList = std::vector<Argument>;

// Arguments are just types with a name to select objects from the current stack frame.
class BaseArgument {
private:
    std::string m_type_name;
    std::string m_value_name;

public:
    BaseArgument();
    explicit BaseArgument(const std::string& type_name, const std::string& value_name);
    virtual ~BaseArgument();

    const std::string& get_type_name() const;
    const std::string& get_value_name() const;
};


class ArgumentRegister : public BaseArgument {
public:
    using BaseArgument::get_type_name;
    using BaseArgument::get_value_name;

    ArgumentRegister(const std::string& type, const std::string& name);
};


class ArgumentConcept : public BaseArgument {
public:
    using BaseArgument::get_type_name;
    using BaseArgument::get_value_name;

    ArgumentConcept(const std::string& type, const std::string& name);
};


}

#endif