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
    Iter<T> begin() const override {
        return Iter<T>(new ListIter<T>(this));
    }

    Iter<T> end() const override {
        return Iter<T>(new ListIter<T>(this, this->Count() > 0 ? this->Count() : 0));
    }

    virtual T RemoveAt(size_t index) = 0;

    virtual T &Get(size_t index) const = 0;

    virtual T &operator[](size_t index) const = 0;

    virtual IList<T> &Set(size_t index, T value) {
        if (index < 0 || index >= this->Count())
            throw range_error("index < 0 or index >= length");
        if constexpr(std::is_const<T>::value) {
            cout << value << endl;
            throw range_error("T is const");
        }
        else{
            Get(index) = value;
        }

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
};

template<typename T>
ostream &operator<<(ostream &out, const IList<T> &x) {
    out << "[";
    size_t length = x.Count();
    size_t i = 0;
    for (auto el: x) {
        Utils::PPrint(out, el);
        if (i != length - 1)
            out << ", ";
        ++i;
    }
    out << "]";
//        out << ")" << endl;
    return out;
}

template<typename T>
istream &operator>>(istream &in, IList<T> &x) {
//    string tmp;
//    getline(in, tmp);
//    stringstream ss(tmp);
    T t;
    while (in >> t) {
        x.Add(t);
    }
    return in;
}
