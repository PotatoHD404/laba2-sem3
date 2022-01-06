//
// Created by kmv026 on 19.12.2021.
//

#pragma once

#include "DynamicArray.hpp"

template<typename T>
class SquareMatrix {
private:
    mutable size_t size;
public:
    mutable DynamicArray<T> data;

    SquareMatrix(size_t size = 0) : size(size), data(size * size) {
    }

    T &Get(size_t i, size_t j) const {
        size_t index;
        if (i >= size || j >= size)
            throw invalid_argument("Wrong indexes");
        if (i >= j)
            index = i * (i + 1) + j;
        else
            index = j * j + i;
        return data[index];
    }

    size_t Size() const {
        return size;
    }

    void Expand(size_t n = 1) {
        size_t sum = 0;
        for (size_t i = 0; i < n + size; ++i) {
            sum += 2 * i + 1;
        }
        size += n;
        data.Resize(sum);
    }

    SquareMatrix(const SquareMatrix &) = default;
};

template<typename T>
ostream &operator<<(ostream &out, const SquareMatrix<T> &x) {
    size_t size = x.Size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            Utils::PPrint(out, x.Get(i, j));
            if (j != size - 1)
                out << ", ";
        }
        if (i != size - 1)
            out << endl;
    }
    return out;
}