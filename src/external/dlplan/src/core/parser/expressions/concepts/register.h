#ifndef DLPLAN_SRC_CORE_PARSER_EXPRESSIONS_CONCEPTS_REGISTER_H_
#define DLPLAN_SRC_CORE_PARSER_EXPRESSIONS_CONCEPTS_REGISTER_H_

#include "../concept.h"
#include "../../utils.h"

using namespace std::string_literals;

namespace dlplan::core::parser
{

    class RegisterConcept : public Concept
    {
    private:
        static inline const std::string m_name = "c_register";

    public:
        RegisterConcept(const std::string &name, std::vector<std::unique_ptr<Expression>> &&children)
            : Concept(name, std::move(children)) {}

        std::shared_ptr<const dlplan::core::Concept> parse_concept(SyntacticElementFactory &factory) const override
        {
            if (m_children.size() != 1)
            {
                throw std::runtime_error("RegisterConcept::parse_concept - number of children ("s + std::to_string(m_children.size()) + " != 2).");
            }
            // 1. Parse children
            int index = try_parse_number(m_children[0]->get_name());
            if (index < 0 || index >= static_cast<int>(factory.get_vocabulary_info()->get_registers().size())) {
                throw std::runtime_error("RegisterConcept::parse_concept - register index out of range.");
            }
            // 2. Construct element
            return factory.make_register_concept(factory.get_vocabulary_info()->get_registers()[index]);
        }

        static const std::string &get_name()
        {
            return m_name;
        }
    };

}

#endif
