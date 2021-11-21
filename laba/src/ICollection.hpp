//
// Created by korna on 03.04.2021.
//
#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"

template<typename T>
class ICollection : public IEnumerable<T> {
public:
    //Decomposition
    using type = T;

    [[nodiscard]] virtual size_t Count() const = 0;

    virtual bool Contains(T item) {
        for (auto el: *this)
            if (el == item)
                return true;
        return false;
    }

    //Operations
    virtual ICollection<T> &Clear() = 0;

    virtual ICollection<T> &Add(T item) = 0;

    virtual T Remove(T item) = 0;

    virtual ~ICollection() = default;
};