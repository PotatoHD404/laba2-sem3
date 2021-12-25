//
// Created by kmv026 on 19.12.2021.
//

#pragma once

#include <random>
#include <chrono>

using namespace std;

template<typename T>
T Random(T min, T max) {
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
    static mt19937 rng(seed);
    if constexpr(std::is_floating_point<T>::value) {
        static uniform_real_distribution<T> distribution(min, max);
        return distribution(rng);
    } else {
        static uniform_int_distribution<T> distribution(min, max);
        return distribution(rng);
    }
}

template<typename T>
T Random() {
    return Random(0, 100);
}


