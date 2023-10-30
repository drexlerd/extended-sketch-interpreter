#ifndef SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_
#define SRC_PARSERS_EXTENDED_SKETCH_DRIVER_HPP_

#include <memory>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/extended_sketch/declarations.hpp"
#include "src/extended_sketch/extended_sketch.hpp"
#include "src/extended_sketch/symbol_handle.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/config.hpp"


namespace sketches::extended_sketch {
struct SymbolTable;
}

namespace sketches::parsers::extended_sketch {

class Driver {
private:
    mimir::formalism::DomainDescription domain_description;
    std::shared_ptr<dlplan::policy::PolicyFactory> policy_factory;
    sketches::extended_sketch::SymbolTable* symbol_table;

public:
    Driver(
        const mimir::formalism::DomainDescription& domain_description,
        const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory,
        sketches::extended_sketch::SymbolTable& symbol_table);

    /// @brief Root call.
    sketches::extended_sketch::Handle<sketches::extended_sketch::ExtendedSketch> parse(
         const std::string& source,
         const std::string& filename="");

    /// @brief Nested call.
    sketches::extended_sketch::Handle<sketches::extended_sketch::ExtendedSketch> parse(
         dlplan::common::parsers::iterator_type& iter,
         dlplan::common::parsers::iterator_type end,
         const std::string& filename="");
};

}


#endif
