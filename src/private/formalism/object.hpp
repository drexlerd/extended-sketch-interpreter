#if !defined(FORMALISM_OBJECT_HPP_)
#define FORMALISM_OBJECT_HPP_

#include "declarations.hpp"
#include "type.hpp"

#include <iostream>
#include <string>

namespace mimir::formalism
{
    class ObjectImpl
    {
      private:
        std::size_t hash_;

      public:
        const uint32_t id;
        const std::string name;
        const formalism::Type type;

        ObjectImpl(const uint32_t id, const std::string& name, const formalism::Type type);

        bool is_free_variable() const;

        bool is_constant() const;

        template<typename T>
        friend class std::hash;
    };

    Object create_object(const uint32_t id, const std::string& name, const formalism::Type type);

    formalism::ObjectList filter(const formalism::ObjectList& object_list, const formalism::Type& type);

    std::ostream& operator<<(std::ostream& os, const formalism::ObjectImpl& object);

    std::ostream& operator<<(std::ostream& os, const formalism::Object& object);

    std::ostream& operator<<(std::ostream& os, const formalism::ObjectList& objects);

}  // namespace formalism

namespace std
{
    // Inject comparison and hash functions to make pointers behave appropriately with ordered and unordered datastructures
    template<>
    struct hash<mimir::formalism::Object>
    {
        std::size_t operator()(const mimir::formalism::Object& object) const;
    };

    template<>
    struct hash<mimir::formalism::ObjectList>
    {
        std::size_t operator()(const mimir::formalism::ObjectList& objects) const;
    };

    template<>
    struct less<mimir::formalism::Object>
    {
        bool operator()(const mimir::formalism::Object& left_object, const mimir::formalism::Object& right_object) const;
    };

    template<>
    struct equal_to<mimir::formalism::Object>
    {
        bool operator()(const mimir::formalism::Object& left_object, const mimir::formalism::Object& right_object) const;
    };

}  // namespace std

#endif  // FORMALISM_OBJECT_HPP_
