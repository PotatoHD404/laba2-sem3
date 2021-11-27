

//
// Created by kmv026 on 07.10.2021.
//
#pragma once

#include <utility>
#include "IEnumerable.hpp"

//template<typename TKey>
//class Enumerable;

template<typename T>
class ISort {
public:
    virtual const IEnumerable<T> &operator()(const IEnumerable<T> &arr) const = 0;
};

namespace std {
    template<typename T>
    int distance(const Iter<T> &ra1, const Iter<T> &ra2) {
        return abs((long) (ra1.GetPos() - ra2.GetPos()));
    }
}
namespace Sorts {
    template<typename T>
    class QuickSort : public ISort<T> {
    private:
    public:

        const IEnumerable<T> &operator()(const IEnumerable<T> &arr) const final {
            quick_sort(arr.begin(), arr.end());
            return arr;
        }

    private:
        /// Quick Sort, allow user-defined less-than operator
        Iter<T> Partition(const Iter<T> &first, const Iter<T> &last) const {
            auto pivot = last - 1;
            auto i = first;
            for (auto j = first; j != pivot; ++j) {
                // bool format
                if (*j < *pivot) {
                    std::swap(*i++, *j);
                }
            }
            std::swap(*i, *pivot);
            return i;
        }

        void quick_sort(const Iter<T> &first, const Iter<T> &last) const {
            if (std::distance(first, last) > 1) {
                Iter<T> bound = Partition(first, last);
                quick_sort(first, bound);
                quick_sort(bound + 1, last);
            }
        }
    };

    template<typename T>
    class ShellSort : public ISort<T> {
    public:
        const IEnumerable<T> &operator()(const IEnumerable<T> &arr) const final {
            shell_sort(arr.begin(), arr.end());
            return arr;
        }

    private:
        void shell_sort(Iter<T> &&first, Iter<T> &&last) const {
            auto size = last - first;
            auto h = 1;
            while (h < (int) (size / 3)) h = 3 * h + 1;

            while (h >= 1) {
                for (auto i = first + h; i != last; i++) {
                    for (auto j = i; (j - first) >= h && *j < *(j - h); j -= h)
                        std::iter_swap(j, j - h);
                }
                h /= 3;
            }
        }

//        static void sort(Iter<TKey> first, Iter<TKey> last) {
//
//        }
    };

    template<typename T>
    class InsertionSort : public ISort<T> {
    public:
        const IEnumerable<T> &operator()(const IEnumerable<T> &arr) const final {
            insertion_sort(arr.begin(), arr.end());
            return arr;
        }

    private:
        void insertion_sort(Iter<T> &&begin, Iter<T> &&end) const {
            iter_swap(begin, min_element(begin, end));
            for (Iter<T> b = begin; ++b < end; begin = b)
                for (Iter<T> c = b; *c < *begin; --c, --begin)
                    iter_swap(begin, c);
        }
    };
}

