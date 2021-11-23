

//
// Created by kmv026 on 07.10.2021.
//
#pragma once

#include <utility>
#include "IEnumerable.hpp"

//template<typename T>
//class Enumerable;

template<typename T>
class ISort {
public:
    virtual const IEnumerable<T> &operator()(const IEnumerable<T> &arr) const = 0;
};

namespace std {
    template<typename T>
    int distance(const Iter<T> &ra1, const Iter<T> &ra2) {
        return abs((long) (ra1 - ra2).GetPos());
    }
}
namespace PrivateSorts {
    template<typename T>
    class QuickSort1 : public ISort<T> {
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
                if (j < pivot) {
                    std::iter_swap(i++, j);
                }
            }
            std::iter_swap(i, pivot);
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
            for (auto d = (last.GetPos()) / 2; d != 0; d /= 2)
                for (auto i = first + d; i != last; ++i)
                    for (auto j = i; j - first >= d && *j < *(j - d); j -= d)
                        iter_swap(j, (j - d));
        }
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

namespace Sorts {
    template<typename T>
    const IEnumerable<T> &QuickSort(const IEnumerable<T> &arr) {
        function<Iter<T>(const Iter<T> &first, const Iter<T> &last)>
                Partition = [&Partition](const Iter<T> &first, const Iter<T> &last) -> Iter<T> {
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
        };

        function<void(const Iter<T> &first, const Iter<T> &last)> quick_sort = [&quick_sort](const Iter<T> &first,
                                                                                             const Iter<T> &last) -> void {
            if (std::distance(first, last) > 1) {
                Iter<T> bound = Partition(first, last);
                quick_sort(first, bound);
                quick_sort(bound + 1, last);
            }
        };
        quick_sort(arr.begin(), arr.end());
        return arr;
    }

    template<typename T>
    static const PrivateSorts::ShellSort<T> ShellSort;

    template<typename T>
    static const PrivateSorts::InsertionSort<T> InsertionSort;

//    enum Sort {
//        Shell, Insertion, Quick
//    };
}



//template<typename T>
//class ISortable {
//public:
//    virtual IEnumerable<T> &Sort(const ISort<T> &sort) = 0;
//};

