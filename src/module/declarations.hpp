#ifndef SRC_MODULE_DECLARATIONS_HPP_
#define SRC_MODULE_DECLARATIONS_HPP_

#include <memory>
#include <unordered_map>
#include <vector>


namespace sketches::module {
    class ModuleImpl;
    using Module = std::shared_ptr<ModuleImpl>;
    using ModuleList = std::vector<Module>;

}

#endif
