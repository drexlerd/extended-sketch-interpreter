#ifndef SRC_EXTENDED_SKETCH_CACHE_HPP_
#define SRC_EXTENDED_SKETCH_CACHE_HPP_

#include <memory>

#include "src/private/dlplan/src/utils/cache.h"

#include "declarations.hpp"


namespace mimir::extended_sketch {

struct Caches {
    std::shared_ptr<dlplan::utils::ReferenceCountedObjectCache<std::string, LoadRuleImpl>> load_rules;
    std::shared_ptr<dlplan::utils::ReferenceCountedObjectCache<std::string, CallRuleImpl>> call_rules;
    std::shared_ptr<dlplan::utils::ReferenceCountedObjectCache<std::string, ActionRuleImpl>> action_rules;
    std::shared_ptr<dlplan::utils::ReferenceCountedObjectCache<std::string, SearchRuleImpl>> search_rules;

    Caches() :
        load_rules(std::make_shared<dlplan::utils::ReferenceCountedObjectCache<std::string, LoadRuleImpl>>()),
        call_rules(std::make_shared<dlplan::utils::ReferenceCountedObjectCache<std::string, CallRuleImpl>>()),
        action_rules(std::make_shared<dlplan::utils::ReferenceCountedObjectCache<std::string, ActionRuleImpl>>()),
        search_rules(std::make_shared<dlplan::utils::ReferenceCountedObjectCache<std::string, SearchRuleImpl>>()) { }
};

}


#endif

