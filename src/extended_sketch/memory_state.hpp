#ifndef SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_
#define SRC_EXTENDED_SKETCH_MEMORY_STATE_HPP_

#include <string>
#include <memory>


namespace sketches::extended_sketch {
class MemoryStateImpl {
private:
    std::string m_key;

public:
    explicit MemoryStateImpl(const std::string& key);

    const std::string& get_key() const;
};

extern std::shared_ptr<MemoryStateImpl> create_memory_state(const std::string& key);

}

#endif
