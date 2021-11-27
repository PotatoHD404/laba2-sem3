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

    ListIter(const ListIter &other) : iterable(*static_cast<IList<T> *>(nullptr)) { *this = other; }


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

    bool Equals(const BaseIter<T> &b) const override {
        return (this->GetPos() == b.GetPos()) && (&this->iterable == &static_cast<const ListIter &>(b).iterable);
    }

    ListIter<T> &operator-=(size_t b_pos) override {
        this->pos -= b_pos;
        return *this;
    }

    ListIter<T> &operator*=(size_t b_pos) override {
        this->pos *= b_pos;
        return *this;
    }

    ListIter<T> &operator/=(size_t b_pos) override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        this->pos /= b_pos;
        return *this;
    }

    ListIter<T> &operator+=(size_t b_pos) override {
        this->pos += b_pos;
        return *this;
    }

    ListIter<T> &operator=(const ListIter<T> &list) {
        if (&this->iterable != &list.iterable)
            throw invalid_argument("Iterables must be equal");
        if (this != &list) {
            this->pos = list.pos;
        }
        return *this;
    }

// c++ stuff

    virtual ~ListIter() = default;
};
