//
// Created by korna on 07.05.2021.
//

#pragma once

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : Pair(first, second) {}

    Pair(T1 first, T2 second) : first(first), second(second) {}

    bool operator==(const Pair &x) const { return first == x.first && second == x.second; }

    bool operator!=(const Pair &x) const {
        return !(x == *this);
    }
};
