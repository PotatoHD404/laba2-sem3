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
private:
    using ptr = lab::shared_ptr<ISequence<T>, ICollection<T>>;
public:
    ISequence() = default;

    virtual ISequence<T> &Concat(ISequence<T> &list) {
        for (auto el : list) {
            this->Add(el);
        }
        return *this;
    }

    virtual ptr AddFirst(T item) = 0;

    virtual ptr nsert(size_t index, T item) = 0;

    virtual T RemoveFirst() = 0;

    virtual T RemoveLast() = 0;

    //Decomposition
    virtual T &First() { return this->Get(0); }

    virtual T &Last() { return this->Get(this->Count() - 1); }

    template<template <typename> class Child, typename T1>
    ptr Map(function<T1(const T&)> mapper){
        auto res = new Child<T1>();
        for(auto el: *this)
            res->Add(mapper());

        return res;
    }

    virtual ~ISequence() = default;
};

template<typename T>
ostream &operator<<(ostream &out, const ISequence<T> &x) {
    out << "[";
    size_t length = x.Count();
    for (size_t i = 0; i < length; ++i) {
        if constexpr(std::is_same<T, string>::value) {
            out << "\'" << x[i] << "\'";
        } else {
            out << x[i];
        }
        if (i != length - 1)
            out << ", ";
    }
    out << "]";
//        out << ")" << endl;
    return out;
}

template<typename T>
istream &operator>>(istream &in, ISequence<T> &x) {
//    string tmp;
//    getline(in, tmp);
//    stringstream ss(tmp);
    T t;
    while (in >> t) {
        x.Add(t);
    }
    return in;
}