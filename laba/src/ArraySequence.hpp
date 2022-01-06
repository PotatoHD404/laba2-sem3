//
// Created by korna on 20.03.2021.
//
#pragma once

#include "DynamicArray.hpp"
#include "ListIter.hpp"
#include "ISequence.hpp"
#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template<typename T>
class ArraySequence : public ISequence<T> {
private:
    mutable DynamicArray<T> items;

public:
    Iter<T> begin() const override { return items.begin(); }

    Iter<T> end() const override { return items.end(); }

    //Creation of the object
    ArraySequence() : items() {}

    explicit ArraySequence(int count) : ArraySequence((size_t) count) {
    }

    ArraySequence(size_t count, T value = T()) : items(count, value) {
    }

    ArraySequence(T *items, size_t count) : items(items, count) {
    }

    template<size_t N>
    explicit ArraySequence(T (&items)[N]) : ArraySequence(items, N) {}

    ArraySequence(initializer_list<T> items) : ArraySequence() {
        for (T item: items)
            this->Add(item);
    }

    ArraySequence(const ArraySequence<T> &list) : items(list.items) {
    }

    explicit ArraySequence(ISequence<T> &list) : ArraySequence((*dynamic_cast<ArraySequence<T> *>(&list))) {}

    explicit ArraySequence(ISequence<T> *list) : ArraySequence(*list) {}

    explicit ArraySequence(const ArraySequence<T> *list) : ArraySequence(*list) {}

    explicit ArraySequence(const unique_ptr<ISequence<T>> &list) : ArraySequence(list.get()) {}

    explicit ArraySequence(const unique_ptr<ArraySequence<T>> &list) : ArraySequence(*list) {}

    //Decomposition



    T &Get(size_t index) const override {
        return items.Get(index);
    }

    ArraySequence<T> *GetSubsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.Count())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.Count())
            throw range_error("endIndex >= length");
        auto *res = new ArraySequence<T>();
        for (size_t i = startIndex; i < endIndex + 1; ++i) {
            res->Add(items.Get(i));
        }
        return res;
    }

    [[nodiscard]] size_t Count() const override {
        return items.Count();
    }

    T RemoveAt(size_t index) override { return items.RemoveAt(index); }

//    bool operator==(const IList<TKey> &list) override {
//        if(this == &list)
//            return true;
//        size_t len = list.Count();
//        if (len != this->Count())
//            return false;
//        for (size_t i = 0; i < len; ++i)
//            if (this->Get(i) != list.Get(i))
//                return false;
//
//        return true;
//    }


    ArraySequence<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.Count())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.Count())
            throw range_error("endIndex >= length");
        auto *res = new ArraySequence<T>();
        res->items = items.GetSubArray(startIndex, endIndex);
        return res;
    }


    //Operations
    template<typename T1>
    ArraySequence<T1> *Init() const {
        return new ArraySequence<T1>();
    }

    template<typename T1>
    ArraySequence<T1> *Init(size_t count) const {
        return new ArraySequence<T1>(count);
    }

    ArraySequence<T> &Resize(size_t count) {
        items.Resize(count);
        return *this;
    }

    ArraySequence<T> &Add(T item) override {
        items.Add(item);
        return *this;
    }

    ArraySequence<T> &AddFirst(T item) override {
        items.Resize(items.Count() + 1);
        for (size_t i = items.Count() - 1; i > 0; --i) {
            items.Set(i, items.Get(i - 1));
        }
        items.Set(0, item);
        return *this;
    }

    ArraySequence<T> &Insert(size_t index, T item) override {
//        if (index == 0)
//            return AddFirst(item);
        if (index > +items.Count() + 1)
            throw range_error("index < 0 or index >= length + 1");
        items.Resize(items.Count() + 1);

        for (size_t i = items.Count() - 1; i > index; --i) {
            items.Set(i, items[i - 1]);
        }
        items.Set(index, item);
        return *this;
    }

    T RemoveFirst() override {
        T res = items.Get(0);
        for (size_t i = 0; i < items.Count() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.Count() - 1);
        return res;
    }

    T RemoveLast() override {
        T res = items.Get(items.Count() - 1);
        items.Resize(items.Count() - 1);
        return res;
    }

    T &operator[](size_t index) const override {
        return items[index];
    }

    ArraySequence<T> &Clear() override {
        items.Clear();
        return *this;
    }

    ArraySequence<T> &operator=(const ArraySequence<T> &) = default;

//    ArraySequence<Seq> *Concat(const ArraySequence<Seq> *list) {
//        return Concat(*list);
//    }

};
