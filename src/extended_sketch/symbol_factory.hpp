#ifndef SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_
#define SRC_EXTENDED_SKETCH_SYMBOL_FACTORY_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>


namespace sketches::extended_sketch {
template<typename Data>
class SymbolFactory;


template<typename Data>
class SymbolHandle {
private:
    int index;

    SymbolHandle(int index_) : index(index_) { }

    friend class SymbolFactory<Data>;

public:
    bool operator==(const SymbolHandle& other) const {
        return index == other.index;
    }

    bool operator!=(const SymbolHandle& other) const {
        return !(*this == other);
    }

    static SymbolHandle undefined;
};

template<typename Data>
SymbolHandle<Data> SymbolHandle<Data>::undefined = SymbolHandle<Data>(-1);


template<typename Data>
class SymbolFactory {
private:
    std::unordered_map<std::string, int> name_to_handle;
    std::vector<Data> datas;

public:
    SymbolHandle<Data> register_symbol(const std::string& name, const Data& data) {
        const auto& it = name_to_handle.find(name);
        if (it != name_to_handle.end()) {
            return SymbolHandle<Data>{it->second};
        }
        int index = data.size();
        name_to_handle.emplace(name, index);
        datas.push_back(data);
        return SymbolHandle<Data>{index};
    }

    SymbolHandle<Data> get_handle(const std::string& name) const {
        assert(name_to_handle.count(name));
        return name_to_handle.at(name);
    }

    Data& get_data(SymbolHandle<Data> handle) {
        assert(handle != SymbolHandle<Data>::undefined);
        return datas[handle.index];
    }

    const Data& get_data(SymbolHandle<Data> handle) const {
        assert(handle != SymbolHandle<Data>::undefined);
        return datas[handle.index];
    }

    Data& operator[](SymbolHandle<Data> handle) {
        return get_data(handle);
    }

    const Data& operator[](SymbolHandle<Data> handle) const {
        return get_data(handle);
    }
};


}

#endif
