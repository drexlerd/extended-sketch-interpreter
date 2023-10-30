#ifndef SRC_EXTENDED_SKETCH_SYMBOL_HANDLE_HPP_
#define SRC_EXTENDED_SKETCH_SYMBOL_HANDLE_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <iostream>


namespace sketches::extended_sketch {
template<typename Symbol>
class Factory;


/// @brief Lightweight reference to the Symbol.
///        This allows fast reference from one place in the ast to another
template<typename Symbol>
class Handle {
private:
    int index;
    // We can think of adding non-owning pointer to factory here.

    Handle(int index_) : index(index_) { }

    friend class Factory<Symbol>;

public:
    Handle() : index(-1) { }  // undefined

    bool operator==(const Handle& other) const {
        return index == other.index;
    }

    bool operator!=(const Handle& other) const {
        return !(*this == other);
    }

    static Handle undefined;
};

template<typename Symbol>
Handle<Symbol> Handle<Symbol>::undefined = Handle<Symbol>(-1);


}

#endif
