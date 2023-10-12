#include "context.hpp"


namespace sketches::extended_sketch::parser {

Context::Context(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::core::SyntacticElementFactory>& syntactic_element_factory,
    const std::shared_ptr<dlplan::policy::PolicyBuilder>& policy_builder)
    : domain_description(domain_description),
      policy_builder(policy_builder),
      memory_state_factory(MemoryStateFactory()),
      register_factory(RegisterFactory()),
      boolean_factory(BooleanFactory(syntactic_element_factory)),
      numerical_factory(NumericalFactory(syntactic_element_factory)),
      concept_factory(ConceptFactory(syntactic_element_factory)) { }
}
