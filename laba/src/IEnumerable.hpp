//
// Created by kmv026 on 06.10.2021.
//
#pragma once

#include "RandomAccessIterator.hpp"
#include "IterImplementation.hpp"

template<typename T>
using Iter = Implementation<RandomAccessIterator<T>>;

template<typename T>
class IEnumerable {
public:
    virtual Iter<T> begin() = 0;

    virtual Iter<T> end() = 0;
};
