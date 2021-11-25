//
// Created by kmv026 on 06.10.2021.
//
#pragma once

#include "BaseIter.hpp"
#include "IterImpl.hpp"

template<typename T>
using Iter = IterImpl<BaseIter<T>>;

template<typename T>
class IEnumerable {
public:
    [[nodiscard]] virtual Iter<T> begin() const = 0;

    [[nodiscard]] virtual Iter<T> end() const = 0;
};
