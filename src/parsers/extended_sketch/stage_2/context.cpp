#include "context.hpp"


namespace sketches::parsers::extended_sketch::stage_2 {

Context::Context(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory)
    : domain_description(domain_description),
      action_schema_map(domain_description->get_action_schema_map()),
      policy_factory(policy_factory),
      memory_state_factory(MemoryStateFactory()),
      register_factory(RegisterFactory()),
      boolean_factory(BooleanFactory(policy_factory)),
      numerical_factory(NumericalFactory(policy_factory)),
      concept_factory(ConceptFactory(policy_factory)) { }
}
