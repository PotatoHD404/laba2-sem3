//
// Created by PotatoHD on 25.11.2021.
//

#pragma once

#include "BaseIter.hpp"


template<typename T>
class GraphIter : public BaseIter<T> {
protected:
    const ICollection<T> *it;
public:
    explicit GraphIter(const ICollection<T> *it, size_t pos = 0) : BaseIter<T>(pos), it(it) {
    }

    GraphIter<T> &operator+=(size_t b_pos) override {
        for (size_t i = 0; i < b_pos; ++i) {
            ++(*this);
        }
        return *this;
    }

    GraphIter<T> &operator-=(size_t b_pos) override {
        for (size_t i = 0; i < b_pos; ++i) {
            --(*this);
        }
        return *this;
    }

    GraphIter<T> &operator*=(size_t b_pos) override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        size_t diff = this->GetPos() * b_pos - this->GetPos();
        for (size_t i = 0; i < diff; ++i) {
            ++(*this);
        }
        return *this;
    }

    bool Equals(const BaseIter<T> &other) const override {
        return ((const GraphIter &) other).it == this->it && this->pos == other.GetPos();
    }

    GraphIter<T> &operator/=(size_t b_pos) override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        size_t diff = this->GetPos() - this->GetPos() / b_pos;
        for (size_t i = 0; i < diff; ++i) {
            --(*this);
        }
        return *this;
    }

};
