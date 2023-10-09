#ifndef SRC_EXTENDED_SKETCH_REGISTER_HPP_
#define SRC_EXTENDED_SKETCH_REGISTER_HPP_

#include <string>
#include <memory>


namespace sketches::extended_sketch {
class RegisterImpl {
private:
    std::string m_key;

public:
    explicit RegisterImpl(const std::string& key);

    const std::string& get_key() const;
};

extern std::shared_ptr<RegisterImpl> make_register(const std::string& key);

}

#endif
