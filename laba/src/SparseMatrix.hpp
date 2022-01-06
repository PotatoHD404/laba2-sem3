//
// Created by kmv026 on 19.12.2021.
//

#pragma once

#include "Dictionary.hpp"

class Point {
private:
    static size_t ComputeIndex(size_t i, size_t j) {
        size_t index;
        if (i >= j)
            index = i * (i + 1) + j;
        else
            index = j * j + i;
        return index;
    }

public:

    size_t i{}, j{}, index{};

    Point() = default;

    Point(size_t i, size_t j) : i(i), j(j), index(ComputeIndex(i, j)) {}

    Point &operator=(const Point &) = default;

    bool operator==(const Point &other) const {
        return this->index == other.index;
    }

    bool operator!=(const Point &x) const {
        return !(*this == x);
    }

    bool operator>(const Point &other) const {
        return this->index > other.index;
    }

    bool operator<(const Point &other) const {
        return this->index < other.index;
    }

    bool operator>=(const Point &other) const {
        return this->index >= other.index;
    }

    bool operator<=(const Point &other) const {
        return this->index <= other.index;
    }
};

template<typename T>
class SparseMatrix : IEnumerable<const KeyValue<Point, T>> {
private:
    mutable size_t height;
    mutable size_t width;
public:


    Iter<const KeyValue<Point, T>> begin() const override {
        return data.begin();
    }

    Iter<const KeyValue<Point, T>> end() const override {
        return data.end();
    }

    mutable Dictionary<Point, T> data{};

    explicit SparseMatrix(size_t height, size_t width) : height(height), width(width) {
    }

    explicit SparseMatrix(size_t size) : height(size), width(size) {
    }

    SparseMatrix(const SparseMatrix &) = default;

    size_t Width() const {
        return width;
    }

    size_t Height() const {
        return height;
    }

    void Expand(size_t n = 1, bool w = true) {
        if (w)
            width += n;
        else
            height += n;
    }

    T Get(size_t i, size_t j) const {

        if (i >= height || j >= width)
            throw invalid_argument("Wrong indexes");
        auto index = Point(i, j);
        if (data.Contains(index))
            return data[index];
        return T();
    }

    void Set(size_t i, size_t j, T value) const {
        if (i >= height || j >= width)
            throw invalid_argument("Wrong indexes");
        auto index = Point(i, j);
        if (data.Contains(index))
            if (value == T())
                data.Remove(index);
            else
                data[index] = value;
        else if (value != T())
            data.Add(index, value);
    }

};

ostream &operator<<(ostream &out, const Point &x) {
    out << '(';
    Utils::PPrint(out, x.i);
    out << ", ";
    Utils::PPrint(out, x.j);
    out << ')';
    return out;
}

template<typename T>
ostream &operator<<(ostream &out, const SparseMatrix<T> &x) {
    size_t width = x.Width();
    size_t height = x.Height();
    ArraySequence<size_t> spaces(x.Width(), 1);
    stringstream str;
    for (auto el: x) {
        str << el.GetValue();
        if (str.str().length() > spaces[el.GetKey().j])
            spaces[el.GetKey().j] = str.str().length();
        str.str(string());
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
//            str << el.GetValue();
            Utils::PPrint(str, x.Get(i, j));
            cout << str.str();
            if (j != width - 1) {
                for (size_t k = 0; k < spaces[j] - str.str().length(); ++k)
                    out << ' ';
                out << ", ";
            }

            str.str(string());
        }
        if (i != height - 1)
            out << endl;
    }
    return out;
}