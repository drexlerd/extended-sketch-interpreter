#ifndef SRC_PARSERS_MODULE_DRIVER_HPP_
#define SRC_PARSERS_MODULE_DRIVER_HPP_

#include <memory>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/module/declarations.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"


namespace sketches::parsers::module {

class Driver {
private:
    mimir::formalism::DomainDescription domain_description;
    std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory;

public:
    Driver(
        const mimir::formalism::DomainDescription& domain_description,
        const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

    /// @brief Root call.
    sketches::module::Module parse(
         const std::string& source,
         const std::string& filename="");

    /// @brief Nested call.
    sketches::module::Module parse(
         dlplan::iterator_type& iter,
         dlplan::iterator_type end,
         const std::string& filename="");
};

}


#endif
