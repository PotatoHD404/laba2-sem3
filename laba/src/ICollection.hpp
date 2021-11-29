//
// Created by korna on 03.04.2021.
//
#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"

//https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly

template<typename T>
class ICollection : public IEnumerable<T> {
public:
    //Decomposition
    using type = T;

    [[nodiscard]] virtual size_t Count() const = 0;

    virtual bool Contains(T item) const {
        for (auto el: *this)
            if (el == item)
                return true;
        return false;
    }

    //Operations
    virtual ICollection<T> &Clear() = 0;

    virtual ICollection<T> &Add(T item) = 0;

    virtual ICollection<T> &Remove(T item) = 0;

    virtual ~ICollection() = default;
};
namespace Utils {
    template<typename T>
    ostream &Print(ostream &out, const T &x) {
        if constexpr(std::is_same<T, string>::value) {
            out << "\'" << x << "\'";
        } else {
            out << x;
        }
        return out;
    }
}

template<typename T>
ostream &operator<<(ostream &out, const ICollection<T> &x) {
    out << "{";
    size_t length = x.Count();
    size_t i = 0;
    for (auto el: x) {
        Utils::Print(out, el);
        if (i != length - 1)
            out << ", ";
        ++i;
    }
    out << "}";
    return out;
}