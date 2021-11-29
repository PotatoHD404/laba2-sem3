//
// Created by korna on 20.03.2021.
//
#pragma once

#include "IList.hpp"
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class ISequence : public IList<T> {
public:

    virtual ISequence &AddFirst(T item) = 0;

    virtual ISequence &Insert(size_t index, T item) = 0;

    virtual T RemoveFirst() = 0;

    virtual T RemoveLast() = 0;

    //Decomposition
    virtual T &First() { return this->Get(0); }

    virtual T &Last() { return this->Get(this->Count() - 1); }

};