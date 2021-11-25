//
// Created by kmv026 on 25.11.2021.
//

#pragma once

#include "IterImpl.hpp"

using namespace std;

//#include "BidirectionalIterator.hpp"
template<typename T>
class BaseIter;

template<typename T>
using Iter = IterImpl<BaseIter<T>>;

template<typename T>
class BaseIter {
protected:
    size_t pos;
public:
    using type = T;
    typedef long difference_type; //almost always ptrdiff_t
    typedef T value_type; //almost always Seq
    typedef T &reference; //almost always Seq& or const Seq&
    typedef T *pointer; //almost always Seq* or const Seq*
    typedef std::random_access_iterator_tag iterator_category;  //usually std::forward_iterator_tag or similar

    explicit BaseIter(size_t pos) : pos(pos) {}

    [[nodiscard]] size_t GetPos() const {
        return pos;
    }

    virtual bool Equals(const BaseIter<T> &b) const = 0;

    virtual T &operator*() const = 0;

    virtual T *operator->() const = 0;

    virtual BaseIter<T> &operator++() = 0;

    virtual BaseIter<T> &operator--() = 0;

    virtual Iter<T> operator+(size_t b_pos) const = 0;

    virtual Iter<T> operator-(size_t b_pos) const = 0;

    virtual Iter<T> operator*(size_t b_pos) const = 0;

    virtual Iter<T> operator/(size_t b_pos) const = 0;

    virtual BaseIter<T> &operator=(const BaseIter<T> &list) = 0;

    Iter<T> operator-(const BaseIter<T> &b) const override {
        return *this - b.GetPos();
    }

    Iter<T> operator+(const BaseIter<T> &b) const override {
        return *this + b.GetPos();
    }

    Iter<T> operator*(const BaseIter<T> &b) const override {
        return *this * b.GetPos();
    }

    Iter<T> operator/(const BaseIter<T> &b) const override {
        return *this / b.GetPos();
    }

    friend bool operator==(const BaseIter<T> &a, const BaseIter<T> &b) {
        return a.Equals(b);
    }

    friend bool operator!=(const BaseIter<T> &a, const BaseIter<T> &b) {
        return !a.Equals(b);
    }

    virtual bool operator<(size_t b_pos) const {
        return this->GetPos() < b_pos;
    }

    virtual bool operator<=(size_t b_pos) const {
        return this->GetPos() <= b_pos;
    }

    virtual bool operator>(size_t b_pos) const {
        return this->GetPos() > b_pos;
    }

    virtual bool operator>=(size_t b_pos) const {
        return this->GetPos() >= b_pos;
    }

    virtual bool operator<(const BaseIter<T> &b) const {
        return this->GetPos() < b.GetPos();
    }

    virtual bool operator<=(const BaseIter<T> &b) const {
        return this->GetPos() <= b.GetPos();
    }

    virtual bool operator>(const BaseIter<T> &b) const {
        return this->GetPos() > b.GetPos();
    }

    virtual bool operator>=(const BaseIter<T> &b) const {
        return this->GetPos() >= b.GetPos();
    }

    virtual ~BaseIter() = default;
};
