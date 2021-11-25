//
// Created by kmv026 on 19.09.2021.
//
#pragma once

#include "BaseIter.hpp"

using namespace std;

//#include "BidirectionalIterator.hpp"
template<typename T>
class IList;


template<typename T>
class ListIter : public BaseIter<T> {
protected:
    const IList<T> &iterable;

public:


    explicit ListIter(const IList<T> &it, size_t pos = 0) : BaseIter<T>(pos), iterable(it) {}

    ListIter(const ListIter &other) : BaseIter<T>(other.pos), iterable(other.iterable) {}


// c++ stuff

    T &operator*() const override { return iterable[this->pos]; }

    T *operator->() const override { return &iterable[this->pos]; }

    ListIter &operator++() override {
        ++this->pos;
        return *this;
    }

    ListIter &operator--() override {
        --this->pos;
        return *this;
    }

    bool Equals(const ListIter &b) const override {
        return (this->GetPos() == b.GetPos()) && (&this->iterable == &b.iterable);
    }

    Iter<T> operator-(size_t b_pos) const override {
        return Iter<T>(ListIter(this->iterable, this->pos - b_pos));
    }

    Iter<T> operator*(size_t b_pos) const override {
        Iter<T>(ListIter(this->iterable, this->pos * b_pos));
    }

    Iter<T> operator/(size_t b_pos) const override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        return Iter<T>(ListIter(this->iterable, this->pos / b_pos));
    }

    Iter<T> operator+(size_t b_pos) const override {
        return Iter<T>(ListIter(this->iterable, this->pos + b_pos));
    }

    ListIter<T> &operator=(const ListIter<T> &list) override {
        if (this != &list) {
            this->iterable = list.iterable;
            this->pos = list.pos;
        }
        return *this;
    }

// c++ stuff

    virtual ~ListIter() = default;
};
