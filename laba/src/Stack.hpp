//
// Created by korna on 05.05.2021.
//

#pragma once

#include "ListSequence.hpp"

template<class T>
class Stack : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

    void Push(T item) {
        this->AddFirst(item);
    }

    T Pop() {
        return this->RemoveFirst();
    }

    T &Top() const {
        return this->Get(0);
    }

    bool IsEmpty() {
        return this->Count() == 0;
    }
};
