//
// Created by korna on 20.03.2021.
//
#pragma once

#include "LinkedList.hpp"
#include <iostream>
#include <cstring>
#include <memory>
#include "ISequence.hpp"


using namespace std;

template<typename T>
class ListSequence : public ISequence<T> {
private:
    mutable LinkedList<T> items;

public:
    Iter<T> begin() const override { return items.begin(); }

    Iter<T> end() const override { return items.end(); }

    ListSequence Copy() {
        return ListSequence<T>(*this);
    }

    //Creation of the object
    ListSequence() : items() {}

    explicit ListSequence(int count) : ListSequence((size_t) count) {
    }

    explicit ListSequence(size_t count) : items(count) {}

    ListSequence(T *items, size_t count) : items(items, count) {
    }

    ListSequence(const ListSequence<T> &list) : items(list.items) {
    }

    template<size_t N>
    explicit ListSequence(T (&items)[N]) : ListSequence(items, N) {}

    ListSequence(initializer_list<T> items) : ListSequence() {
        for (T item: items)
            this->Add(item);
    }

    explicit ListSequence(const LinkedList<T> &list) : items(list) {
    }

    explicit ListSequence(ISequence<T> &list) : ListSequence((*dynamic_cast<ListSequence<T> *>(&list))) {
    }

    explicit ListSequence(ISequence<T> *list) : ListSequence(*list) {
    }

    explicit ListSequence(const ListSequence<T> *list) : ListSequence(*list) {
    }

    explicit ListSequence(const unique_ptr<ISequence<T>> &list) : ListSequence(list.get()) {
    }

    explicit ListSequence(const unique_ptr<ListSequence<T>> &list) : ListSequence(*list) {
    }

    //Decomposition

    T &Get(size_t index) const override {
        return items.Get(index);
    }

    ListSequence<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.Count())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.Count())
            throw range_error("endIndex >= length");
        auto *res = new ListSequence<T>();
        res->items = items.GetSubList(startIndex, endIndex);
        return res;
    }

    [[nodiscard]] size_t Count() const override {
        return items.Count();
    }

    T &operator[](size_t index) const override {
        return items[index];
    }
//    virtual bool operator==(const ISequence<Seq> &list) = 0;

//    virtual bool operator==(const ListSequence<TKey> &list) {
//        return items == list.items;
//    }

    //Operations
    ListSequence<T> &Clear() override {
        while (items.Count()) items.RemoveFirst();
        return *this;
    }

//    ListSequence<Seq> Copy() const {
//        return ListSequence<Seq>(this->items);
//    }

    ListSequence<T> &Add(T item) override {
        items.Add(item);
        return *this;
    }

    ListSequence<T> &AddFirst(T item) override {
        items.AddFirst(item);
        return *this;
    }

    ListSequence<T> &Insert(size_t index, T item) override {
        items.Insert(index, item);
        return *this;
    }

    T RemoveFirst() override {
        return items.RemoveFirst();
    }

    T RemoveLast() override {
        return items.RemoveLast();
    }

    ListSequence &operator=(const ListSequence &) = default;

    T RemoveAt(size_t index) override {
        if (index < 0 || index >= items.Count())
            throw range_error("index < 0 or index >= length");
        return items.RemoveAt(index);
    }

};