//
// Created by kmv026 on 19.09.2021.
//
#pragma once

#include "IterImplementation.hpp"

using namespace std;

//#include "BidirectionalIterator.hpp"
template<typename T>
class IList;


template<typename T>
class RandomAccessIterator {
protected:
    using Iter = Implementation<RandomAccessIterator<T>>;
    size_t pos;
    IList<T> &iterable;

//    using IEnumerator = IEnumerator<Seq, RandomAccessIterator>;

public:
    using type = T;
    typedef long difference_type; //almost always ptrdiff_t
    typedef T value_type; //almost always Seq
    typedef T &reference; //almost always Seq& or const Seq&
    typedef T *pointer; //almost always Seq* or const Seq*
    typedef std::random_access_iterator_tag iterator_category;  //usually std::forward_iterator_tag or similar


    explicit RandomAccessIterator(IList<T> &it, size_t pos = 0) : pos(pos), iterable(it) {}

    RandomAccessIterator(const RandomAccessIterator &other) : pos(other.pos), iterable(other.iterable) {}




//    explicit IEnumerator(Iter<Seq> &it, size_t pos) = 0;

//    IEnumerator(const IEnumerator &other) = 0;
//    virtual Child<Seq> Init() = 0;


//    virtual Seq *operator->() const = 0;

    // Prefix increment

    // Postfix increment

    [[nodiscard]] size_t GetPos() const {
        return pos;
    }

    friend bool operator==(const RandomAccessIterator &a, const RandomAccessIterator &b) {
        return a.Equals(b);
    }

    friend bool operator!=(const RandomAccessIterator &a, const RandomAccessIterator &b) {
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
    virtual RandomAccessIterator &operator++() {
        ++this->pos;
        return *this;
    }

    virtual RandomAccessIterator &operator--() {
        --this->pos;
        return *this;
    }

    // Postfix increment
    virtual Iter operator++(int) { // NOLINT(cert-dcl21-cpp)
        RandomAccessIterator tmp = RandomAccessIterator(*this);
        ++(*this);
        return Iter(tmp);
    }

    virtual Iter operator--(int) { // NOLINT(cert-dcl21-cpp)
        RandomAccessIterator tmp = RandomAccessIterator(*this);
        --(*this);
        return Iter(tmp);
    }

    virtual bool Equals(const RandomAccessIterator &b) const {
        return (this->iterable == b.iterable) && (this->GetPos() == b.GetPos());
    }

    virtual Iter operator-(const RandomAccessIterator &b) const {
//        IEnumerator &tmp = RandomAccessIterator(*this);
        return Iter(RandomAccessIterator(this->iterable, this->pos - b.GetPos()));
    }

    virtual Iter operator-(const size_t &b) const {
        return Iter(RandomAccessIterator(this->iterable, this->pos - b));
    }

//    IEnumerator &operator/(const IEnumerator *b) const override {
//        return new IEnumerable(this->iterable, this->pos / b);
//    }

    virtual Iter operator/(const size_t &b) const {
        if (b == 0)
            throw invalid_argument("b equals 0");
        return Iter(RandomAccessIterator(this->iterable, this->pos / b));
    }

    virtual Iter operator+(const RandomAccessIterator &b) const {
        return Iter(RandomAccessIterator(this->iterable, this->pos + b.GetPos()));
    }

    virtual Iter operator+(const size_t &b) const {
        return Iter(RandomAccessIterator(this->iterable, this->pos + b));
    }

    virtual bool operator<(const size_t &b) const {
        return this->GetPos() < b;
    }

    virtual bool operator<=(const size_t &b) const {
        return this->GetPos() <= b;
    }

    virtual bool operator>(const size_t &b) const {
        return this->GetPos() > b;
    }

    virtual bool operator>=(const size_t &b) const {
        return this->GetPos() >= b;
    }

    virtual bool operator<(const RandomAccessIterator<T> &b) const {
        return this->GetPos() < b.GetPos();
    }

    virtual bool operator<=(const RandomAccessIterator<T> &b) const {
        return this->GetPos() <= b.GetPos();
    }

    virtual bool operator>(const RandomAccessIterator<T> &b) const {
        return this->GetPos() > b.GetPos();
    }

    virtual bool operator>=(const RandomAccessIterator<T> &b) const {
        return this->GetPos() >= b.GetPos();
    }

    RandomAccessIterator<T> &operator=(const RandomAccessIterator<T> &list) {
        if (this != &list) {
            this->iterable = list.iterable;
            this->pos = list.pos;
        }
        return *this;
    }

// c++ stuff

   virtual ~RandomAccessIterator() = default;
};
