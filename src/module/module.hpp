#ifndef SRC_MODULE_MODULE_HPP_
#define SRC_MODULE_MODULE_HPP_

#include <string>
#include <unordered_map>

#include "src/extended_sketch/extended_sketch.hpp"
#include "signature.hpp"


namespace sketches::extended_sketch {

class ModuleImpl {
private:
    Signature signature;

    std::shared_ptr<ExtendedSketch> extended_sketch;

public:
    ModuleImpl();
};

}

#endif