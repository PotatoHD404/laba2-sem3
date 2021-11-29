#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <type_traits>
#include <limits>
#include <chrono>
#include "Complex.hpp"
#include "Exceptions.hpp"
#include "ListSequence.hpp"
#include "ArraySequence.hpp"
#include "Sorts.hpp"
#include "Utils.hpp"
#include "Dictionary.hpp"

using namespace std;
using namespace Utils;

const int itemNum = 2;

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
        uniform_int_distribution<int> distribution(-itemNum * 10, itemNum * 10);
        return (int) distribution(rng);
    } else if constexpr(std::is_same<T, float>::value) {
        uniform_real_distribution<float> distribution(-10, 10);
        return (float) distribution(rng);
    } else {
        throw NotImplemented("", "");
    }
}

template<typename T>
auto test_data() {
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
    static mt19937 rng = mt19937(seed);
    static array<T, itemNum> data;
    static bool called;
    if (!called) {
        generate(
                data.begin(), data.end(), []() { return GenRandom<T>(rng); });
        called = true;
    }
    return data;
}


int main() {
    Dictionary<string, int> dictionary;
    dictionary.Add("a", 4);
//    dictionary.Remove("a");
    cout << dictionary.values << endl;
    return 0;
}