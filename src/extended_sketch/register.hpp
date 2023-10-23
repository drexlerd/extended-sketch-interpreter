#ifndef SRC_EXTENDED_SKETCH_REGISTER_HPP_
#define SRC_EXTENDED_SKETCH_REGISTER_HPP_

#include <string>
#include <memory>


namespace sketches::extended_sketch {
// We could take the registers that we implement in dlplan to avoid having to synchronize the contents.
class RegisterImpl {
private:
    std::string m_key;

public:
    explicit RegisterImpl(const std::string& key);

    const std::string& get_key() const;
};

extern std::shared_ptr<RegisterImpl> create_register(const std::string& key);

}

#endif
