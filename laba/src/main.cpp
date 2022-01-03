#include <iostream>
#include "SquareMatrix.hpp"
#include "SparseMatrix.hpp"
#include "Graph.hpp"
#include "Random.hpp"

using namespace std;


int main() {
    Graph<int> a(2, 1, false, false, true);

    cout << a.GraphvizPrint() << endl;
//    SparseMatrix<size_t> a(100);
//    SquareMatrix<size_t> a(3);
//
//    a.Set(1, 0, 20);
//    a.Set(2, 0, 35);
//    a.Set(2, 0, 0);
//
//    a.Set(0, 2, 100);
//    cout << a << endl;
//
//    cout << a.data << endl;
//
//    for (const auto& el: a) {
//        cout << el << endl;
//    }
//
//
//    a.Expand(1);
//    cout << a << endl;
//    cout << a.Size() << endl;
//    a.Get(2, 1) = 1;
//
//    for (size_t i = 0; i < a.data.Count(); ++i) {
//        a.data[i] = i;
//    }
//    a.Expand();
//    cout << a << endl;
//    cout << a.data << endl;
//
//    for (size_t i = 0; i < a.data.Count(); ++i) {
//        a.data[i] = i;
//    }
//    cout << a << endl;
//    cout << a.data << endl;
//    cout << a.Get(0, 4) << endl;


    return 0;
}