//
// Created by PotatoHD on 25.11.2021.
//

#pragma once

#include "BaseIter.hpp"


template<typename T>
class GraphIter : public BaseIter<T> {
protected:
    const ICollection<T> &iterable;
public:
    explicit GraphIter(const ICollection<T> &it, size_t pos = 0) : BaseIter<T>(pos), iterable(it) {}

    GraphIter(const GraphIter &other) : BaseIter<T>(other.pos), iterable(other.iterable) {}

    bool Equals(const GraphIter &b) const override {
        return (this->GetPos() == b.GetPos()) && (&this->iterable == &b.iterable);
    }

    Iter<T> operator-(size_t b_pos) const override {
        auto res = Iter<T>(GraphIter(this->iterable));
        for (int i = 0; i < b_pos; ++i) {
            res--;
        }
        return res;
    }

    Iter<T> operator/(size_t b_pos) const override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        auto res = Iter<T>(GraphIter(this->iterable));
        size_t diff = res.GetPos() - res.GetPos() / b_pos;
        for (int i = 0; i < diff; ++i) {
            res--;
        }
        return res;
    }

    Iter<T> operator*(size_t b_pos) const override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        auto res = Iter<T>(GraphIter(this->iterable));
        size_t diff = res.GetPos() * b_pos - res.GetPos();
        for (int i = 0; i < diff; ++i) {
            res++;
        }
        return res;
    }

    Iter<T> operator+(size_t b_pos) const override {
        auto res = Iter<T>(GraphIter(this->iterable));
        for (int i = 0; i < b_pos; ++i) {
            res++;
        }
        return res;
    }

};
