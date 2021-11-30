//
// Created by PotatoHD on 29.11.2021.
//

#pragma once

#include "ICollection.hpp"

template<typename T1, typename T2>
class MapCollection : public ICollection<T1> {
private:
    const ICollection<T2> &dict;

    T1 &(*bijectiveFunc)(T2 &);

    class Iterator : public BaseIter<T1> {
    private:
        Iter<T2> iter;

        T1 &(*bijectiveFunc)(T2 &);

    public:
        explicit Iterator(Iter<T2> iter, T1 &(*bijectiveFunc)(T2 &)) : BaseIter<T1>(0), iter(iter), bijectiveFunc(bijectiveFunc){
        }

        Iterator(const Iterator &other) : BaseIter<T1>(0), iter(other.iter), bijectiveFunc(other.bijectiveFunc) {
        }

        [[nodiscard]] size_t GetPos() const override {
            return iter.GetPos();
        }

        bool Equals(const BaseIter<T1> &b) const override {
            return iter == dynamic_cast<const Iterator &>(b).iter &&
                   bijectiveFunc == dynamic_cast<const Iterator &>(b).bijectiveFunc;
        }

        T1 *operator->() const override { return &(**this); }

        T1 &operator*() const override { return bijectiveFunc(*iter); }

        // Prefix increment
        Iterator &operator++() override {
            ++(iter);
            return *this;
        }
        // Prefix increment

        Iterator &operator--() override {
            --(iter);
            return *this;
        }

        Iterator &operator+=(size_t num) override {
            this->iter += num;
            return *this;
        };

        Iterator &operator-=(size_t num) override {
            this->iter -= num;
            return *this;
        };

        Iterator &operator*=(size_t num) override {
            this->iter *= num;
            return *this;
        };

        Iterator &operator/=(size_t num) override {
            this->iter /= num;
            return *this;
        };
    };

public:
    Iter<T1> begin() const override {
        return Iter<T1>(new Iterator(dict.begin(), bijectiveFunc));
    }

    Iter<T1> end() const override {
        return Iter<T1>(new Iterator(dict.end(), bijectiveFunc));
    }

    MapCollection(const MapCollection &dict) = delete;


    explicit MapCollection(const ICollection<T2> *dict, T1 &(*bijectiveFunc)(T2 &)) : dict(*dict),
                                                                                      bijectiveFunc(bijectiveFunc) {}

    [[nodiscard]] size_t Count() const override { return dict.Count(); }

    MapCollection &operator=(const MapCollection &) = delete;

private:
    ICollection<T1> &Clear() override { throw NotImplemented(); }

    ICollection<T1> &Add(T1) override { throw NotImplemented(); }

    ICollection<T1> &Remove(T1) override { throw NotImplemented(); }
};
