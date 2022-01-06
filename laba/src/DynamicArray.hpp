//
// Created by korna on 20.03.2021.
//
#pragma once

#include <iostream>
#include <cstring>
#include "IList.hpp"

using namespace std;

template<class T>
class DynamicArray : public IList<T> {
private:
    T *actual_array;
    size_t length{};

public:
    //Creation of the object
    DynamicArray() : actual_array(new T[1]()), length(0) {}

    explicit DynamicArray(size_t count, T value = T()) {
        if ((long) count < 0)
            throw out_of_range("count < 0");

        if (count > 0)
            actual_array = new T[count];
        else
            actual_array = new T[1]();
        length = count;
        for (size_t i = 0; i < length; ++i) {
            actual_array[i] = value;
        }
    }

    DynamicArray(T *items, size_t count) {
        if ((long) count < 0)
            throw out_of_range("count < 0");
        if (items == NULL)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            actual_array = new T[count]();
            memcpy(actual_array, items, count * sizeof(T));
        } else {
            actual_array = new T[1]();
        }
        length = count;
    }

    DynamicArray(const DynamicArray<T> &list) : DynamicArray() {
        *this = list;
    }

    //Decomposition
    T &Get(size_t index) const override {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        return actual_array[index];
    }

    T &operator[](size_t index) const override { return actual_array[index]; }

    DynamicArray<T> &Clear() override {
        this->Resize(0);
        return *this;
    }

    ICollection<T> &Add(T item) override {
        this->Resize(this->Count() + 1);
        this->Set(this->Count() - 1, item);
        return *this;
    }

    T RemoveAt(size_t index) override {

        if (index < 0 || index >= this->Count())
            throw range_error("index < 0 or index >= length");
        T res = this->Get(index);
        for (size_t i = index; i < this->Count() - 1; ++i) {
            this->Set(i, this->Get(i + 1));
        }
        this->Resize(this->Count() - 1);
        return res;
    }

    DynamicArray<T> &Set(size_t index, T value) override {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        Get(index) = value;
        return *this;
    }

    DynamicArray<T> GetSubArray(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= length)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= length)
            throw range_error("endIndex >= length");
        size_t len = endIndex - startIndex + 1;

        DynamicArray<T> res(len);
        for (size_t i = startIndex; i < len; ++i) {
            res.actual_array[i] = actual_array[i];
        }
//        memcpy(res.actual_array, this->actual_array + startIndex, len * sizeof(Seq));
        return res;
    }

    [[nodiscard]] size_t Count() const override { return length; }

    //Operations
    DynamicArray<T> &Resize(size_t new_length) {
        if (new_length < 0) {
            throw range_error("new_length < 0");
        }
        T *new_array;

        if (new_length > 0) {
            new_array = new T[new_length]();
            size_t len = new_length > length ? length : new_length;
            for (size_t i = 0; i < len; ++i) {
                new_array[i] = actual_array[i];
            }
        } else new_array = new T[1]();
        delete[] actual_array;
        length = new_length;
        actual_array = new_array;
        return *this;
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &list) {
        if (&list != this) {
//            this->~DynamicArray();
            if (actual_array) {
                delete[] actual_array;
                actual_array = nullptr;
            }
            length = list.Count();
            if (length > 0) {
                actual_array = new T[length]();
                for (size_t i = 0; i < length; ++i) {
                    actual_array[i] = list.actual_array[i];
                }
            } else
                actual_array = new T[1]();
        }
        return *this;
    }

    //Termination
    ~DynamicArray() {
        delete[] actual_array;
    }
};