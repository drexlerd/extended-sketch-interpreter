#ifndef SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_

#include <memory>

#include "src/external/dlplan/include/dlplan/core.h"
#include "src/external/dlplan/include/dlplan/policy.h"
#include "src/external/mimir/formalism/domain.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/parsers/common/config.hpp"


namespace sketches::parsers::extended_sketch {
class Driver {
private:
     mimir::formalism::DomainDescription domain_description;
     std::shared_ptr<dlplan::core::SyntacticElementFactory> element_factory;
     std::shared_ptr<dlplan::policy::PolicyBuilder> policy_builder;

public:
     Driver(
        const mimir::formalism::DomainDescription& domain_description,
        const std::shared_ptr<dlplan::core::SyntacticElementFactory>& element_factory,
        const std::shared_ptr<dlplan::policy::PolicyBuilder>& policy_builder);

     /// @brief Root call.
     sketches::extended_sketch::ExtendedSketch parse(
          const std::string& filename,
          const std::string& source);

     /// @brief Nested call.
     sketches::extended_sketch::ExtendedSketch parse(
          const std::string& filename,
          iterator_type& iter,
          iterator_type end);
};

}


#endif
