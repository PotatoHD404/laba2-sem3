//
// Created by kmv026 on 13.10.2021.
//
#pragma once

#include "ICollection.hpp"
#include "ISortable.hpp"

template<typename T>
class IList : public ICollection<T>, public ISortable<T> {
public:
    Iter<T> begin() const override {
        return Iter<T>(RandomAccessIterator<T>(*this));
    }

    Iter<T> end() const override {
        return Iter<T>(RandomAccessIterator<T>(*this, this->Count() > 0 ? this->Count() : 0));
    }

    virtual T RemoveAt(size_t index) = 0;

    virtual T &Get(size_t index) const = 0;

    virtual T &operator[](size_t index) const = 0;

    virtual IList<T> &Set(size_t index, T value) {
        if (index < 0 || index >= this->Count())
            throw range_error("index < 0 or index >= length");
        Get(index) = value;
        return *this;
    }

    T Remove(T item) override {
        for (auto ptr = this->begin(); ptr < this->end(); ptr++)
            if (*ptr == item)
                return this->RemoveAt(ptr.GetPos());
        throw invalid_argument("Item was not found");
    }

    virtual bool operator==(const IList<T> &list) const {
        if (list.Count() != this->Count())
            return false;
        for (Iter<T> iter1 = this->begin(), iter2 = list.begin(); iter1.GetPos() < list.Count(); iter1++, iter2++) {
            if (*iter1 != *iter2) {
                return false;
            }
        }
        return true;
    }

    virtual IList<T> &Sort() { return this->Sort(Sorts::QuickSort<T>); }

    IList<T> &Sort(const ISort<T> &sort) final {
        return (IList<T> &) sort(*this);
    }

    virtual ~IList() = default;
};
