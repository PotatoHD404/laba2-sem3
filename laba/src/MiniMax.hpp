//
// Created by PotatoHD on 08.12.2021.
//

#pragma  once

#include "Pair.hpp"

class Pole {
private:
    mutable char *pole;
public:
    const size_t size{};

    Pole(size_t size) : size(size), pole{new char[size * size]} {}

    char &operator[](Pair<size_t> pair) const {
        return this->Get(pair.first, pair.second);
    }

    char &Get(size_t i, size_t j) const {
        return pole[i * size + j];
    }

    char GameEnded() const {
        bool draw = true;
        char *col = new char[size]();
        char d1{};
        char d2{};
        for (size_t i = 0; i < size; ++i) {
            char row = this->Get(i, 0);
            for (size_t j = 0; j < size; ++j) {
                if (this->Get(i, j) == '_')
                    draw = false;

                if (row != '_') {
                    if (row != this->Get(i, j)) {
                        row = '_';
                    }
                }
                if (col[j] != 0 && col[j] != '_') {
                    if (col[j] != this->Get(i, j)) {
                        col[j] = '_';
                    }
                } else {
                    col[j] = this->Get(i, j);
                }
            }
            if (row != '_')
                return row;
            if (d1 != 0 && d1 != '_') {
                if (d1 != this->Get(i, i)) {
                    d1 = '_';
                }
            } else {
                d1 = this->Get(i, i);
            }
            if (d2 != 0 && d2 != '_') {
                if (d2 != this->Get(size - 1 - i, size - 1 - i)) {
                    d2 = '_';
                }
            } else {
                d2 = this->Get(size - 1 - i, size - 1 - i);
            }
        }
        if (draw)
            return 'd';
        if (d1 != '_')
            return d1;
        if (d2 != '_')
            return d2;
        for (size_t i = 0; i < size; ++i) {
            if (col[i] != '_')
                return col[i];
        }
        return {};
    }
};

// enemy - x
// ally - o

int8_t MiniMax(Pole pole, bool enemy) {
    int8_t bestScore = -2;
    int8_t worstScore = 2;
    char ended = pole.GameEnded();
    if (ended == 'd')
        return 0;
    if (ended != '_') {
        if (enemy)
            return ended == 'x' ? -1 : 1;
        else
            return ended == 'o' ? -1 : 1;
    }
    for (size_t i = 0; i < pole.size; ++i) {
        for (size_t j = 0; j < pole.size; ++j) {
            if (pole[Pair(i, j)] != '_') {
                pole[Pair(i, j)] = enemy ? 'x' : 'o';
                auto x = MiniMax(pole, !enemy);
                if (x > bestScore && !enemy) bestScore = x;
                else if (x < worstScore && enemy) worstScore = x;
            }
        }
    }

    return {};
}
