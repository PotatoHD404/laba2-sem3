//
// Created by kmv026 on 19.09.2021.
//
#pragma once

#include "IterImpl.hpp"

using namespace std;

//#include "BidirectionalIterator.hpp"
template<typename T>
class IList;


template<typename T>
class RAIter {
protected:
    using Iter = IterImpl<RAIter<T>>;
    size_t pos;
    const IList<T> &iterable;

//    using IEnumerator = IEnumerator<Seq, RAIter>;

public:
    using type = T;
    typedef long difference_type; //almost always ptrdiff_t
    typedef T value_type; //almost always Seq
    typedef T &reference; //almost always Seq& or const Seq&
    typedef T *pointer; //almost always Seq* or const Seq*
    typedef std::random_access_iterator_tag iterator_category;  //usually std::forward_iterator_tag or similar


    explicit RAIter(const IList<T> &it, size_t pos = 0) : pos(pos), iterable(it) {}

    RAIter(const RAIter &other) : pos(other.pos), iterable(other.iterable) {}




//    explicit IEnumerator(Iter<Seq> &it, size_t pos) = 0;

//    IEnumerator(const IEnumerator &other) = 0;
//    virtual Base<Seq> Init() = 0;


//    virtual Seq *operator->() const = 0;

    // Prefix increment

    // Postfix increment

    [[nodiscard]] size_t GetPos() const {
        return pos;
    }

    friend bool operator==(const RAIter &a, const RAIter &b) {
        return a.Equals(b);
    }

    friend bool operator!=(const RAIter &a, const RAIter &b) {
        return !a.Equals(b);
    }


// c++ stuff




    virtual T &operator*() const { return iterable[this->pos]; }

    virtual T *operator->() { return &iterable[this->pos]; }

//    operator int() const
//    {
//        return this->pos;
//    }

    // Prefix increment
    virtual RAIter &operator++() {
        ++this->pos;
        return *this;
    }

    virtual RAIter &operator--() {
        --this->pos;
        return *this;
    }

    // Postfix increment
    virtual Iter operator++(int) { // NOLINT(cert-dcl21-cpp)
        RAIter tmp = RAIter(*this);
        ++(*this);
        return Iter(tmp);
    }

    virtual Iter operator--(int) { // NOLINT(cert-dcl21-cpp)
        RAIter tmp = RAIter(*this);
        --(*this);
        return Iter(tmp);
    }

    virtual bool Equals(const RAIter &b) const {
        return (this->GetPos() == b.GetPos()) && (&this->iterable == &b.iterable);
    }

    virtual Iter operator-(const RAIter &b) const {
//        IEnumerator &tmp = RAIter(*this);
        return Iter(RAIter(this->iterable, this->pos - b.GetPos()));
    }

    virtual Iter operator-(size_t b_pos) const {
        return Iter(RAIter(this->iterable, this->pos - b_pos));
    }

    virtual Iter operator*(size_t b_pos) {
        Iter(RAIter(this->iterable, this->pos * b_pos));
    }

    virtual Iter operator/(size_t b_pos) const {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        return Iter(RAIter(this->iterable, this->pos / b_pos));
    }

    virtual Iter operator+(const RAIter &b) const {
        return Iter(RAIter(this->iterable, this->pos + b.GetPos()));
    }

    virtual Iter operator+(size_t b_pos) const {
        return Iter(RAIter(this->iterable, this->pos + b_pos));
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

    virtual bool operator<(const RAIter<T> &b) const {
        return this->GetPos() < b.GetPos();
    }

    virtual bool operator<=(const RAIter<T> &b) const {
        return this->GetPos() <= b.GetPos();
    }

    virtual bool operator>(const RAIter<T> &b) const {
        return this->GetPos() > b.GetPos();
    }

    virtual bool operator>=(const RAIter<T> &b) const {
        return this->GetPos() >= b.GetPos();
    }

    RAIter<T> &operator=(const RAIter<T> &list) {
        if (this != &list) {
            this->iterable = list.iterable;
            this->pos = list.pos;
        }
        return *this;
    }

// c++ stuff

    virtual ~RAIter() = default;
};
