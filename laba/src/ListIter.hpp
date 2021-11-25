//
// Created by PotatoHD on 25.11.2021.
//

#pragma once

#include "RAIter.hpp"

template<typename T>
class ListIter : public RAIter<T> {
public:
    Iter<T> operator-(const RAIter<T> &b) const override {
        return *this - b.GetPos();
    }

    Iter<T> operator+(const RAIter<T> &b) const override {
        return *this + b.GetPos();
    }

    Iter<T> operator*(const RAIter<T> &b) const override {
        return *this * b.GetPos();
    }

    Iter<T> operator/(const RAIter<T> &b) const override {
        return *this / b.GetPos();
    }

    Iter<T> operator-(size_t b_pos) const override {
        auto res = Iter<T>(ListIter(this->iterable));
        for (int i = 0; i < b_pos; ++i) {
            res--;
        }
        return res;
    }

    Iter<T> operator/(size_t b_pos) const override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        auto res = Iter<T>(ListIter(this->iterable));
        size_t diff = res.GetPos() - res.GetPos() / b_pos;
        for (int i = 0; i < diff; ++i) {
            res--;
        }
        return res;
    }

    Iter<T> operator*(size_t b_pos) const override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        auto res = Iter<T>(ListIter(this->iterable));
        size_t diff = res.GetPos() * b_pos - res.GetPos();
        for (int i = 0; i < diff; ++i) {
            res++;
        }
        return res;
    }

    Iter<T> operator+(size_t b_pos) const override {
        auto res = Iter<T>(ListIter(this->iterable));
        for (int i = 0; i < b_pos; ++i) {
            res++;
        }
        return res;
    }

};
