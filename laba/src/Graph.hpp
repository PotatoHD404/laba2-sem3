//
// Created by kmv026 on 19.12.2021.
//

#pragma once

#include "Random.hpp"

template<typename T>
class Graph {
private:


    SparseMatrix<T> data{};
    ArraySequence<T> values{};
public:

//    Iter<T> begin() const override {}

    Graph() = default;

    Graph(size_t height, size_t width) : data(height, width) {}

    Graph(size_t height, size_t width, size_t num) : Graph(height, width) {
        if (width * height < num)
            throw invalid_argument("Too many nodes to generate");
        for (size_t k = 0; k < num; ++k) {
            auto i = Random<size_t>(0, data.Height() - 1), j = Random<size_t>(0, data.Width() - 1);
            if (data.Get(i, j) == T()) {
                T rnd;
                do {
                    rnd = Random<T>();
                } while (rnd == T());
                data.Set(i, j, rnd);
            } else
                --i;
        }
    }

    string GraphvizPrint() {
        stringstream ss;
        for (auto node: data) {
            ss << node.GetKey().i << "->" << node.GetKey().j << "[label=" << node.GetValue() << "];" << endl;
        }
        return ss.str();
    }


};
