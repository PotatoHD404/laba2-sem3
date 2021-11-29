//
// Created by PotatoHD on 23.11.2021.
//

#pragma once

#include "ISequence.hpp"
#include "Sorts.hpp"

namespace Utils {
    template<class T>
    T &unmove(T &&t) { return t; }

    template<typename T, template<typename> class Sequence>
    Sequence<T> Concat(const Sequence<T> &seq1, const Sequence<T> &seq2) {
        Sequence<T> res(seq1);
        for (auto el: seq2) {
            res.Add(el);
        }
        return res;
    }


    template<template<typename> class SortType = Sorts::QuickSort, typename T,
            template<typename> class Sequence>
    Sequence<T> Sort(const Sequence<T> &seq) {
        Sequence<T> res(seq);
        SortType<T> sort;
        sort(res);
        return res;
    }

    template<typename T, template<typename> class Sequence>
    Sequence<T> Copy(const Sequence<T> &seq) {
        return Sequence<T>(seq);
    }

    template<typename T1, typename T, template<typename> class Sequence>
    Sequence<T1> New(const Sequence<T> &) {
        return Sequence<T1>();
    }

    template<typename T1, typename T, template<typename> class Sequence>
    Sequence<T1> Map(const Sequence<T> &seq, function<T1(T)> bijectiveFunc) {
        Sequence<T1> res;
        for (auto el: seq)
            res.Add(bijectiveFunc(el));
        return res;
    }

    template<typename T, template<typename> class Sequence>
    Sequence<T> Where(const Sequence<T> &seq, function<bool(T)> predicate) {
        Sequence<T> res;
        for (auto el: seq)
            if (predicate(el))
                res.Add(el);
        return res;
    }

    template<typename T, template<typename> class Sequence>
    T Reduce(const Sequence<T> &seq, function<T(T, T)> reducer, T c) {
        for (auto el: seq) {
            c = reducer(el, c);
        }
        return c;
    }

    template<typename T, template<typename> class Sequence>
    auto Split(const Sequence<T> &seq, size_t pos) {
        return make_tuple(Subsequence(seq, 0, pos), Subsequence(seq, pos + 1, seq.Count() - 1));
    }

    template<typename T, template<typename> class Sequence>
    Sequence<T> Subsequence(const Sequence<T> &seq, size_t begin, size_t end) {
        Sequence<T> res;
        if (end >= res.Count() || begin < 0 || begin > end)
            throw invalid_argument("Wrong begin or end");
        for (size_t i = begin; i < end; ++i) {
            res.Add(seq[i]);
        }
        return res;
    }

    template<typename T, template<typename> class Sequence>
    Sequence<T> Union(const Sequence<T> &first, const Sequence<T> &second) {
        Sequence<T> res = Sequence<T>(first);
        for (auto el: second) {
            res.Add(el);
        }
        return res;
    }


    template<typename T, template<typename> class Sequence>
    Sequence<T> Intersection(const Sequence<T> &first, const Sequence<T> &second) {
        Sequence<T> res = Sequence<T>();
        auto begin1 = first.begin();
        auto end1 = first.end();
        auto begin2 = second.begin();
        auto end2 = second.end();
//        size_t begin1 = 0, begin2 = 0;
        while (true) {
            if (*begin1 == *begin2) {
                res.Add(*begin1);
                ++begin1;
                ++begin2;
            } else if (*begin1 < *begin2) {
                if (++begin1 >= end1)
                    break;
            } else {
                if (++begin2 >= end2)
                    break;
            }
        }
        return res;
    }


    template<typename T, template<typename> class Sequence>
    Sequence<T> Difference(const Sequence<T> &first, const Sequence<T> &second) {
        Sequence<T> res = Sequence<T>(first);
        for (auto el: second) {
            res.Remove(el);
        }
        return res;
    }
}