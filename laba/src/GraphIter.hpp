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

    GraphIter<T> &operator-=(size_t b_pos) override {
        for (int i = 0; i < b_pos; ++i) {
            ++(*this);
        }
        return *this;
    }

    GraphIter<T> &operator/=(size_t b_pos) override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        size_t diff = this->GetPos() - this->GetPos() / b_pos;
        for (int i = 0; i < diff; ++i) {
            --(*this);
        }
        return *this;
    }

    GraphIter<T> &operator*=(size_t b_pos) override {
        if (b_pos == 0)
            throw invalid_argument("b equals 0");
        size_t diff = this->GetPos() * b_pos - this->GetPos();
        for (int i = 0; i < diff; ++i) {
            ++(*this);
        }
        return *this;
    }

    GraphIter<T> &operator+=(size_t b_pos) override {
        for (int i = 0; i < b_pos; ++i) {
            ++(*this);
        }
        return *this;
    }

    bool Equals(const BaseIter<T> &b) const override {
        return (this->GetPos() == b.GetPos()) && (&this->iterable == &static_cast<const GraphIter &>(b).iterable);
    }

};
