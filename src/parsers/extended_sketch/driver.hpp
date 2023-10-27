#ifndef SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_

#include <memory>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/extended_sketch/extended_sketch.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;
}

namespace sketches::parsers::extended_sketch {

class Driver {
private:
    mimir::formalism::DomainDescription domain_description;
    std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory;

public:
    Driver(
        const mimir::formalism::DomainDescription& domain_description,
        const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory);

    /// @brief Root call.
    sketches::extended_sketch::ExtendedSketchHandle parse(
         const std::string& source,
         sketches::extended_sketch::SymbolTable& parent_symbol_table,
         const std::string& filename="");

    /// @brief Nested call.
    sketches::extended_sketch::ExtendedSketchHandle parse(
         dlplan::common::parsers::iterator_type& iter,
         dlplan::common::parsers::iterator_type end,
         sketches::extended_sketch::SymbolTable& parent_symbol_table,
         const std::string& filename="");
};

}


#endif
