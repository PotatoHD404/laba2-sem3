//
// Created by PotatoHD on 25.11.2021.
//

#pragma once

#include "ListSequence.hpp"

template<class T>
class Queue : ListSequence<T> {
public:
    Queue() = default;

    void Push(T item) {
        this->AddFirst(item);
    }

    T Pop() {
        return this->RemoveLast();
    }

    T &Top() {
        return this->GetLast();
    }

    bool IsEmpty() {
        return this->Count() == 0;
    }
};
