//
// Created by kmv026 on 06.10.2021.
//
#pragma once

#include "RAIter.hpp"
#include "IterImpl.hpp"

template<typename T>
using Iter = IterImpl<RAIter<T>>;

template<typename T>
class IEnumerable {
public:
    virtual Iter<T> begin() const = 0;

    virtual Iter<T> end() const= 0;
};
