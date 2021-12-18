//
// Created by PotatoHD on 15.12.2021.
//

#pragma once

#include "Pairs.hpp"
#include "Set.hpp"

class Board {

public:
    const size_t size{};
    const size_t winConst{};

    class Point {
    public:
        mutable size_t x;
        mutable size_t y;

        Point() = default;

        Point(size_t x, size_t y) : x(x), y(y) {}

        bool operator==(const Point &p) const { return x == p.x && y == p.y; }

        bool operator!=(const Point &p) const {
            return !(p == *this);
        }
    };

    class Cluster {
    private:
        Point leftUpper{}, rightLower{};
    public:
        Cluster() = default;

        Cluster(const Cluster &) = default;

        Cluster(Point leftUpper, Point rightLower) : leftUpper(leftUpper), rightLower(rightLower) {
        }

        explicit Cluster(Point point, size_t expand = 5) {
            size_t x = point.x > expand ? point.x - expand : 0;
            size_t y = point.y > expand ? point.y - expand : 0;
            leftUpper = {x, y};
            rightLower = {point.x + expand, point.y + expand};
        }

        bool Contains(Point point) const {
            return leftUpper.x <= point.x && point.x <= rightLower.x && leftUpper.y <= point.y &&
                   point.y <= rightLower.y;
        }

        bool IsNear(Point point) const {
            return leftUpper.x <= point.x + 5 && point.x <= rightLower.x + 5 && leftUpper.y <= point.y + 5 &&
                   point.y <= rightLower.y + 5;
        }

        bool operator==(const Cluster &) const = default;

        void Expand(Point point) {
            if (point.x < leftUpper.x)
                leftUpper.x = point.x;
            else if (point.x > rightLower.x)
                rightLower.x = point.x;
            if (point.y < leftUpper.y)
                leftUpper.y = point.y;
            else if (point.y > rightLower.y)
                rightLower.y = point.y;

        }
    };

private:
    mutable ArraySequence<char> board;
    mutable char gameState{};
    mutable size_t count{};
    ArraySequence<Cluster> clusters;
public:


    explicit Board(size_t size) : size(size), board(size * size, '_'), clusters(), winConst(5 < size ? 5 : size) {
    }

    Board(const Board &) = default;

    char operator[](Pair<size_t> pair) const {
        return this->Get(pair.first, pair.second);
    }


    char Get(size_t i, size_t j) const {
        return board[i * size + j];
    }

    void Set(size_t i, size_t j, char item) const {
        if (board[i * size + j] != '_' || gameState != 0)
            throw invalid_argument("Wrong move!");
        board[i * size + j] = item;
        ++count;
        if (count == size * size) {
            gameState = '_';
            return;
        }
        size_t expand = winConst - 1;
        size_t leftBound = j >= expand ? j - expand : 0;
        size_t rightBound = j + expand < this->size ? j + expand : this->size - 1;
        size_t upBound = i >= expand ? i - expand : 0;
        size_t downBound = i + expand < this->size ? i + expand : this->size - 1;
        bool won = true;
        if (rightBound - leftBound >= winConst) {
            for (size_t k = leftBound; k < rightBound; ++k) {
                if (this->Get(i, k) != item) {
                    won = false;
                    break;
                }
            }
            if (won) {
                gameState = item;
                return;
            }
            won = true;
        }
        if (downBound - upBound >= winConst) {
            for (size_t k = downBound; k < upBound; ++k) {
                if (this->Get(k, j) != item) {
                    won = false;
                    break;
                }
            }
            if (won) {
                gameState = item;
                return;
            }
            won = true;
        }
        auto min = (long long) (leftBound - j > upBound - i ? leftBound - j : upBound - i);
        auto max = (long long) (rightBound - j > downBound - i ? downBound - i : rightBound - j);
        for (long long k = min; k < max; ++k) {
            if (this->Get(i + k, j + k) != item) {
                won = false;
                break;
            }
        }
        if (won) {
            gameState = item;
            return;
        }
        won = true;
        min = (long long) (leftBound - j > -(downBound - i) ? leftBound - j : -(downBound - i));
        max = (long long) (rightBound - j > i- upBound ? upBound - i : rightBound - j);
        for (long long k = min; k < max; ++k) {
            if (this->Get(i + k, j - k) != item) {
                won = false;
                break;
            }
        }
        if (won) {
            gameState = item;
            return;
        }




//
//
//        if (j >= expand) {
//
//        }
//        if () {
//
//        }
//        if (j + expand < this->size) {
//
//        }
    }

    void UpdateClusters(size_t i, size_t j) {
        for (auto cluster: clusters) {
            if (cluster.IsNear({i, j})) {
                cluster.Expand({i, j});
                break;
            }
        }
    }

    bool IsInClusters(size_t i, size_t j) {
        for (auto cluster: clusters) {
            if (cluster.Contains({i, j}))
                return true;
        }
        return false;
    }

    char GetGameState() const {
//        bool draw = true;
//        auto *col = new Pair<char, uint8_t>[size]{};
//        Pair<char, uint8_t> d1{};
//        Pair<char, uint8_t> d2{};
//        for (size_t i = 0; i < size; ++i) {
//            Pair<char, uint8_t> row = {};
//            for (size_t j = 0; j < size; ++j) {
//                if (this->Get(i, j) == '_')
//                    draw = false;
//
//                if (row.first != this->Get(i, j)) {
//                    row.first = this->Get(i, j);
//                    row.second = 1;
//                } else {
//                    ++row.second;
//                }
//                if (col[j].first != this->Get(i, j)) {
//                    col[j].first = this->Get(i, j);
//                    col[j].second = 1;
//                } else {
//                    ++col[j].second;
//                }
//
//                if (row.second == winConst && row.first != '_')
//                    return row.first;
//                if (col[j].second == winConst && col[j].first != '_')
//                    return col[j].first;
//            }
//            if (d1.first != this->Get(i, i)) {
//                d1.first = this->Get(i, i);
//                d1.second = 1;
//            } else {
//                ++d1.second;
//            }
//            size_t k = size - 1 - i;
//            if (d2.first != this->Get(i, k)) {
//                d2.first = this->Get(i, k);
//                d2.second = 1;
//            } else {
//                ++d2.second;
//            }
//            if (d1.second == winConst && d1.first != '_')
//                return d1.first;
//            if (d1.second == winConst && d1.first != '_')
//                return d1.first;
//        }
//        if (draw)
//            return '_';
//        return 0;
        return gameState;
    }

};

ostream &operator<<(ostream &out, const Board &x) {
    for (size_t i = 0; i < x.size; ++i) {
        for (size_t j = 0; j < x.size; ++j) {
            cout << x.Get(i, j);
        }
        cout << endl;
    }
    return out;
}