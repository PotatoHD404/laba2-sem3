//
// Created by kmv026 on 13.10.2021.
//
#pragma once

#include "ICollection.hpp"
#include "ListIter.hpp"
#include "Sorts.hpp"

template<typename T>
class IList : public ICollection<T> {
public:
    Iter<T> begin() override {
        return Iter<T>(ListIter<T>(*this));
    }

    Iter<T> end() override {
        return Iter<T>(ListIter<T>(*this, this->Count() > 0 ? this->Count() : 0));
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

    IList<T> &Remove(T item) override {
        for (auto ptr = this->begin(); ptr < this->end(); ptr++)
            if (*ptr == item) {
                this->RemoveAt(ptr.GetPos());
                return *this;
            }
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

    virtual IList &operator=(const IList &) = 0; // NOLINT(misc-unconventional-assign-operator)

    virtual ~IList() = default;
};

