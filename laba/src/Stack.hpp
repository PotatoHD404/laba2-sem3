//
// Created by korna on 05.05.2021.
//

#pragma once

#include "ListSequence.hpp"

template<class T>
class Stack : ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

    void Push(T item) {
        this->AddFirst(item);
    }

    T Pop() {
        return this->RemoveFirst();
    }

    T & Top() const {
        return this->GetFirst();
    }

    bool IsEmpty() {
        return this->Count() == 0;
    }
};
