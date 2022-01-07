//
// Created by PotatoHD on 15.12.2021.
//

#pragma once

#include "Pairs.hpp"
#include "Set.hpp"

class Board {

public:
    const size_t size{};
    const long winConst{};

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

//        Cluster(const Cluster &) = default;

        Cluster(Point leftUpper, Point rightLower) : leftUpper(leftUpper), rightLower(rightLower) {
        }

        explicit Cluster(size_t x, size_t y, size_t expand = 5) {
            size_t x1 = x > expand ? x - expand : 0;
            size_t y1 = y > expand ? y - expand : 0;
            leftUpper = {x1, y1};
            rightLower = {x + expand, y + expand};
        }

        bool Contains(size_t x, size_t y) const {
            return leftUpper.x <= x && x <= rightLower.x && leftUpper.y <= y &&
                   y <= rightLower.y;
        }

        bool IsNear(size_t x, size_t y) const {
            return leftUpper.x <= x + 5 && x <= rightLower.x + 5 && leftUpper.y <= y + 5 &&
                   y <= rightLower.y + 5;
        }

        size_t GetSize() const {
            return (rightLower.x - leftUpper.x + 1) * (rightLower.y - leftUpper.y + 1);
        }

        bool operator==(const Cluster &other) const {
            return leftUpper == other.leftUpper && rightLower == other.rightLower;
        }

        bool operator!=(const Cluster &other) {
            return !(other == *this);
        }

        void Expand(size_t x, size_t y) {
            if (x < leftUpper.x)
                leftUpper.x = x;
            else if (x > rightLower.x)
                rightLower.x = x;
            else if (x == leftUpper.x && x > 0)
                leftUpper.x = x - 1;
            else if (x == rightLower.x)
                rightLower.x = x + 1;
            if (y < leftUpper.y)
                leftUpper.y = y;
            else if (y > rightLower.y)
                rightLower.y = y;
            else if (y == leftUpper.y && y > 0)
                leftUpper.y = y - 1;
            else if (y == rightLower.y)
                rightLower.y = y + 1;

//            if (leftUpper.y == (size_t) -1) {
//                cout << "" << endl;
//            }

        }

        friend ostream &operator<<(ostream &out, const Cluster &x) {
            out << "(";
            out << x.leftUpper.x << ", " << x.leftUpper.y << ", ";
            out << x.rightLower.x << ", " << x.rightLower.y;

            out << ")";
            return out;
        }
    };

public:
    mutable char *board;
    mutable char gameState{};
    mutable size_t count{};
    ListSequence<Cluster> clusters;
    Stack<Stack<Pair<Cluster, size_t>>> clusterChanges;
    long score{};
public:


    explicit Board(size_t size) : size(size), winConst(5 < size ? 5 : size), board(new char[size * size]), clusters() {
        for (size_t i = 0; i < size * size; ++i) {
            board[i] = '_';
        }
    }

    long GetScore() const { return score; }

    Board(const Board &) = default;

//    char operator[](Pair<size_t> pair) const {
//        return this->Get(pair.first, pair.second);
//    }


    char Get(size_t i, size_t j) const {
        return board[i * size + j];
    }

    size_t GetSize() const {
//        size_t res = 0;
//        for (auto cluster: clusters) {
//            res += cluster.GetSize();
//        }
        return size * size;
    }

    size_t GetCount() const {
        return count;
    }

    void Set(size_t i, size_t j, char item, bool updateClusters = true) {
        if (item == '_') {
            gameState = 0;
            if (board[i * size + j] != '_')
                --count;
            board[i * size + j] = item;
            return;
        }
        if (board[i * size + j] != '_' || gameState != 0)
            throw invalid_argument("Wrong move!");
        board[i * size + j] = item;
        if (updateClusters)
            this->UpdateClusters(i, j);
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
        long series = 0;
        for (size_t k = leftBound; k <= rightBound; ++k) {
            if (this->Get(i, k) != item) {
                series = 0;
            } else {
                ++series;
            }
            if (series == winConst) {
                gameState = item;
                return;
            }
        }

        series = 0;


        for (size_t k = upBound; k <= downBound; ++k) {
            if (this->Get(k, j) != item) {
                series = 0;
            } else {
                ++series;
            }
            if (series == winConst) {
                gameState = item;
                return;
            }
        }
        series = 0;

        auto min = (long long) (leftBound - j > upBound - i ? leftBound - j : upBound - i);
        auto max = (long long) (rightBound - j > downBound - i ? downBound - i : rightBound - j);
        if (max - min >= (long long) expand) {
            for (long long k = min; k <= max; ++k) {
                if (this->Get(i + k, j + k) != item) {
                    series = 0;
                } else {
                    ++series;
                }
                if (series == winConst) {
                    gameState = item;
                    return;
                }
            }
            series = 0;
        }
        min = (long long) (leftBound - j > -(downBound - i) ? leftBound - j : -(downBound - i));
        max = (long long) (rightBound - j > i - upBound ? i - upBound : rightBound - j);
        if (max - min >= (long long) expand) {
            for (long long k = min; k <= max; ++k) {
                if (this->Get(i - k, j + k) != item) {
                    series = 0;
                } else {
                    ++series;
                }
                if (series == winConst) {
                    gameState = item;
                    return;
                }
            }
        }
    }

    void UpdateClusters(size_t i, size_t j) {
        bool added = false;
        clusterChanges.Push(Stack<Pair<Cluster, size_t>>());
        for (size_t k = 0; k < clusters.Count(); ++k) {

            if (clusters[k].IsNear(i, j)) {
                clusterChanges.Top().Push(Pair(clusters[k], k));
                clusters[k].Expand(i, j);
                added = true;
//                break;
            }
        }
        if (!added) {
            Cluster tmp = {Point(i, j), Point(i, j)};
            tmp.Expand(i, j);
            tmp.Expand(i, j);
            clusterChanges.Top().Push(Pair(Cluster(Point((size_t) -1, (size_t) -1),
                                                   Point((size_t) -1, (size_t) -1)), clusters.Count()));
            clusters.Add(tmp);
        }
    }

    void UndoClusters() {
        auto changes = clusterChanges.Pop();
        while (!changes.IsEmpty())
            if (Cluster(Point((size_t) -1, (size_t) -1),
                        Point((size_t) -1, (size_t) -1)) == changes.Top().first)
                clusters.RemoveAt(changes.Pop().second);
            else {
                auto tmp = changes.Pop();
                clusters[tmp.second] = tmp.first;
            }

    }

    bool IsInClusters(size_t i, size_t j) const {
        for (auto cluster: clusters) {
            if (cluster.Contains(i, j))
                return true;
        }
        return false;
    }

    char GetGameState() const {
        return gameState;
    }

    ~Board() {
        delete[] board;
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