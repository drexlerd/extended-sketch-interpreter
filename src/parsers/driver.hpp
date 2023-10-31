#ifndef SRC_PARSERS_DRIVER_HPP_
#define SRC_PARSERS_DRIVER_HPP_

#include <memory>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"
#include "semantic/context.hpp"

namespace sketches::extended_sketch {

class Driver {
private:
    mimir::formalism::DomainDescription domain_description;
    std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory;

public:
    Driver(
        const mimir::formalism::DomainDescription& domain_description,
        const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

    /// @brief Root call.
    ExtendedSketch parse_sketch(
        const std::string& source,
        const std::string& filename="");

    /// @brief Nested call.
    ExtendedSketch parse_sketch(
        dlplan::iterator_type& iter,
        dlplan::iterator_type end,
        dlplan::error_handler_type& error_handler,
        Context& context,
        const std::string& filename="");


    /// @brief Root call.
    Module parse_module(
        const std::string& source,
        const std::string& filename="");

    /// @brief Nested call.
    Module parse_module(
        dlplan::iterator_type& iter,
        dlplan::iterator_type end,
        dlplan::error_handler_type& error_handler,
        Context& context,
        const std::string& filename="");
};

}


#endif
