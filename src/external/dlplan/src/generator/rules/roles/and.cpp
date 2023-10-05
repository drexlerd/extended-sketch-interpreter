#include "and.h"

#include "../../generator_data.h"

#include "../../../core/parser/expressions/roles/and.h"


namespace dlplan::generator::rules {
void AndRole::generate_impl(const core::States& states, int target_complexity, GeneratorData& data, core::DenotationsCaches& caches) {
    core::SyntacticElementFactory& factory = data.m_factory;
    for (int i = 1; i < target_complexity - 1; ++i) {
        int j = target_complexity - i - 1;
        for (const auto& r1 : data.m_roles_by_iteration[i]) {
            for (const auto& r2 : data.m_roles_by_iteration[j]) {
                auto element = factory.make_and_role(r1, r2);
                auto denotations = element->evaluate(states, caches);
                if (data.m_role_hash_table.insert(denotations).second) {
                    data.m_reprs.push_back(element->compute_repr());
                    data.m_roles_by_iteration[target_complexity].push_back(std::move(element));
                    increment_generated();
                } else {
                    caches.role_denotations_cache.erase_denotation(element->get_index(), -1, -1);
                }
            }
        }
    }
}

const std::string& AndRole::get_name() const {
    return core::parser::AndRole::get_name();
}

}
