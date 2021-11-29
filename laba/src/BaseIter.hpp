//
// Created by kmv026 on 25.11.2021.
//

#pragma once


using namespace std;

//#include "BidirectionalIterator.hpp"
template<typename T>
class BaseIter;

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

    [[nodiscard]] virtual size_t GetPos() const {
        return pos;
    }

    virtual bool Equals(const BaseIter<T> &b) const = 0;

    virtual T &operator*() const = 0;

    virtual T *operator->() const = 0;

    virtual BaseIter<T> &operator++() = 0;

    virtual BaseIter<T> &operator--() = 0;

    virtual BaseIter<T> &operator+=(size_t b_pos) = 0;

    virtual BaseIter<T> &operator-=(size_t b_pos) = 0;

    virtual BaseIter<T> &operator*=(size_t b_pos) = 0;

    virtual BaseIter<T> &operator/=(size_t b_pos) = 0;

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
