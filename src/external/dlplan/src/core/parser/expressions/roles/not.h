#ifndef DLPLAN_SRC_CORE_PARSER_EXPRESSIONS_ROLES_NOT_H_
#define DLPLAN_SRC_CORE_PARSER_EXPRESSIONS_ROLES_NOT_H_

#include "../role.h"

using namespace std::string_literals;


namespace dlplan::core::parser {

class NotRole : public Role {
private:
    static inline const std::string m_name = "r_not";

public:
    NotRole(const std::string &name, std::vector<std::unique_ptr<Expression>> &&children)
    : Role(name, std::move(children)) { }

    std::shared_ptr<const dlplan::core::Role> parse_role(SyntacticElementFactory& factory) const override {
        if (m_children.size() != 1) {
            throw std::runtime_error("NotRole::parse_role - number of children ("s + std::to_string(m_children.size()) + " != 1).");
        }
        // 1. Parse children
        auto role = m_children[0]->parse_role(factory);
        if (!role) {
            throw std::runtime_error("NotRole::parse_role - child is not of type Role.");
        }
        // 2. Construct element
        return factory.make_not_role(role);
    }

    static const std::string& get_name() {
        return m_name;
    }
};

}

#endif
