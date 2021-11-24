#define _CRTDBG_MAP_ALLOC

#include <map>
#include <iostream>
#include <vector>
#include <random>
#include <array>
#include "Utils.hpp"
#include "ArraySequence.hpp"
#include "Complex.hpp"

using namespace std;
using namespace Utils;

template<class Iter>
void insertion_sort(Iter begin, Iter end) {
    iter_swap(begin, min_element(begin, end));
    for (Iter b = begin; ++b < end; begin = b)
        for (Iter c = b; *c < *begin; --c, --begin)
            iter_swap(begin, c);
}

template<typename T>
T GenRandom(mt19937 &rng) {
    if constexpr(std::is_same<T, string>::value) {
        static string alphanum = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
        uniform_int_distribution<unsigned> distribution(0, alphanum.length() - 1);
        string res;
        for (int i = 0; i < 5; ++i) {
            res += alphanum[distribution(rng)];
        }
        return res;
    } else if constexpr(std::is_same<T, Complex>::value) {
        uniform_real_distribution<float> distribution(-1, 1);
        return Complex((float) distribution(rng), (float) distribution(rng));
    } else if constexpr(std::is_same<T, int>::value) {
        uniform_int_distribution<int> distribution(-1000, 1000);
        return (int) distribution(rng);
    } else if constexpr(std::is_same<T, float>::value) {
        uniform_real_distribution<float> distribution(-10, 10);
        return (float) distribution(rng);
    } else {
        throw NotImplemented("", "");
    }
}

int main() {
    ArraySequence<int> a;
//    cout << Sort<Sorts::ShellSort>(a) << endl;
//    cout << Sort<Sorts::QuickSort>(a) << endl;
    static random_device rd;
    static mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
                    chrono::duration_cast<chrono::seconds>(
                            chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (mt19937::result_type)
                    chrono::duration_cast<chrono::microseconds>(
                            chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    static auto rng = mt19937(seed);
    static array<int, 10000> data;

    generate(data.begin(), data.end(), []() { return GenRandom<int>(rng); });
    for (int i = 0; i < 10000; ++i) {
        a.Add(data[i]);
    }
    vector<int> b(data.begin(), data.end());
    insertion_sort(b.begin(), b.end());
    insertion_sort(a.begin(), a.end());
    for (size_t i = 0; i < b.size(); i++)
        cout << b[i] << " " << a[i] << endl;
    return 0;
}