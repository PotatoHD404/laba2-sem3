//
// Created by korna on 17.05.2021.
//

#pragma once

#include "BTree.hpp"
#include "ISequence.hpp"
#include "ISet.hpp"

template<typename T>
class Set : ISet<T> {
private:
    BTree<T> items;

    template<typename TKey, typename TValue>
    friend
    class Dictionary;

    typename BTree<T>::BNode *Find(T key) const {
        return this->items.root->Search(key);
    }

public:

    Iter<const T> begin() const override { return items.begin(); }

    Iter<const T> end() const override {
        return items.end();
    }

    //Creation of the object
    Set() : items() {}

    Set(T *items, size_t count) : items(items, count) {
    }

    Set(initializer_list<T> const &items) : Set() {
        for (T item: items)
            this->Add(item);
    }

    Set(Set<T> &list) : items(list.items) {}

    explicit Set(const Set<T> *list) : Set(*list) {}

    //Decomposition

    Set<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        Set<T> *res = new Set<T>();
        res->items = items.GetSubList(startIndex, endIndex);
        return res;
    }

    [[nodiscard]] size_t Count() const override {
        return items.Count();
    }

    //Operations
    Set &Clear() override {
        items = BTree<T>();
        return *this;
    }

    T Pop() {
        return items.Pop();
    }

    Set &Add(T item) override {
        items.Add(item);
        return *this;
    }

    bool Contains(T item) const override {
        return items.Contains(item);
    }

    Set &Remove(T item) override {
        items.Remove(item);
        return *this;
    }

    Set<T> Union(Set<T> &list) {
        Set<T> res = Set<T>(*this);
        ArraySequence<T> arr = list.items.ToArraySequence();
        for (size_t i = 0; i < arr.Count(); ++i) {
            res.Add(arr[i]);
        }
        return res;
    }

    string AsTree() {
        return items.Order();
    }

    Set<T> Intersection(Set<T> &list) {
        Set<T> res = Set<T>();
        ArraySequence<T> arr1 = items.ToArraySequence();
        ArraySequence<T> arr2 = list.items.ToArraySequence();
        size_t i = 0, j = 0;
        while (true) {
            if (arr1[i] == arr2[j]) {
                res.Add(arr1[i]);
                i++;
                j++;
            } else if (arr1[i] < arr2[j]) {
                if (i == arr1.Count() - 1)
                    break;
                i++;
            } else if (arr1[i] > arr2[j]) {
                if (j == arr2.Count() - 1)
                    break;
                j++;
            }
        }
        return res;
    }

    Set<T> Difference(Set<T> &list) {
        Set<T> res = Set<T>(*this);
        ArraySequence<T> arr = list.items.ToArraySequence();
        for (size_t i = 0; i < arr.Count(); ++i) {
            res.Remove(arr[i]);
        }
        return res;
    }

    ArraySequence<T> ToArraySequence() {
        return items.ToArraySequence();
    }
//    bool operator==(Set<TKey> &x) { return x.items == this->items; }
//    bool operator==(Set<TKey> &&x) { return x.items == this->items; }

    bool operator==(Set<T> &list) {
        return list.items.ToArraySequence() == items.ToArraySequence();
    }

    bool operator==(Set<T> &&list) {
        return list.items.ToArraySequence() == items.ToArraySequence();
    }

    bool operator!=(const Set<T> &x) const {
        return x.items != this->items;
    }

    Set<T> &operator+=(const Set<T> &list) {
        *this = *this + list;
        return *this;
    }

    Set<T> &operator*=(const Set<T> &list) {
        *this = *this * *list;
        return *this;
    }

    Set<T> &operator-=(const Set<T> &list) {
        *this = *this - list;
        return *this;
    }

    Set<T> operator+(Set<T> &list) {
        return Union(list);
    }

    Set<T> operator*(Set<T> &list) {
        return Intersection(list);
    }

    Set<T> operator-(Set<T> &list) {
        return Difference(list);
    }
};

template<typename T>
ostream &operator<<(ostream &out, const Set<T> &x) {
    ArraySequence<T> tmp = x.items.ToArraySequence();
    out << "{";
    size_t length = tmp.Count();
    for (size_t i = 0; i < length; ++i) {
        if constexpr(std::is_same<T, string>::value) {
            out << "\'" << x[i] << "\'";
        } else {
            out << x[i];
        }
        if (i != length - 1)
            out << ", ";
    }
    out << "}";
    return out;
}

template<typename T>
istream &operator>>(istream &in, Set<T> &x) {
    string tmp;
    getline(in, tmp);
    stringstream ss(tmp);
    T t;
    while (ss >> t) {
        x.Add(t);
    }
    return in;
}