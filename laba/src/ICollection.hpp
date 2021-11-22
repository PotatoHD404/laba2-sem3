//
// Created by korna on 03.04.2021.
//
#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"
#include "CollectionFactory.hpp"

//https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly

template<typename T>
class ICollection : public IEnumerable<T> {
protected:
    template<typename T1>
    const static CollectionFactory<ICollection, T1> factory;
public:
    //Decomposition
    using type = T;

    [[nodiscard]] virtual size_t Count() const = 0;

    virtual bool Contains(T item) {
        for (auto el: *this)
            if (el == item)
                return true;
        return false;
    }

    //Operations
    virtual ICollection<T> &Clear() = 0;

    virtual ICollection<T> &Add(T item) = 0;

    virtual ICollection<T> &&Copy() = 0;

    virtual T Remove(T item) = 0;

    virtual ~ICollection() = default;
};

template<template<typename> class Child,typename T>
class CopyHelper : public ICollection<T>{
    Child<T> &&Copy() override {
        auto res = Child<T>();
        return move(res);
    }
};