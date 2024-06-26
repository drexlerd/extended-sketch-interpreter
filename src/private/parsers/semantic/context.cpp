#include "context.hpp"


namespace mimir::extended_sketch {

Context::Context(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory)
    : domain_description(domain_description),
      action_schema_map(domain_description->get_action_schema_map()),
      dlplan_context(*policy_factory) { }
}
