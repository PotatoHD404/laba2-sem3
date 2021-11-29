//
// Created by PotatoHD on 28.11.2021.
//

#pragma once

#include "Set.hpp"
#include "Pair.hpp"
#include "IDictionary.hpp"

template<typename TKey, typename TValue>
class Dictionary : IDictionary<TKey, TValue> {
private:
    using ICollection = ICollection<KeyValue<TKey, TValue>>;
    using KeyValue = KeyValue<TKey, TValue>;
    Set<KeyValue> set;

public:
    template<typename T>
    class KeySet : public ISet<T> {
        Dictionary *dict;
    };

    template<typename T>
    class ValueSet : public ISet<T> {
        Dictionary *dict;
    };


    TValue &Get(TKey key) const override {
        auto pair = KeyValue(key, TValue());
        auto node = set.Find(pair);
        if (node == nullptr)
            throw invalid_argument("Key was not found");
        for (KeyValue &el: node->values) {
            if (el == pair) {
                return el.GetValue();
            }
        }
        throw invalid_argument("Key was not found");
    }

    TValue &operator[](TKey key) const override { return this->Get(key); }

    Iter<const KeyValue> begin() const override { return set.begin(); }

    Iter<const KeyValue> end() const override { return set.end(); }

    [[nodiscard]] size_t Count() const override { return set.Count(); }

//    TValue &Get(TKey key) {
//        return set.Get(Pair(key, TValue()));
//    }

    Dictionary &Add(KeyValue item) override {
        set.Add(item);
        return *this;
    }

    Dictionary &Remove(KeyValue item) override {
        set.Remove(item);
        return *this;
    }

    Dictionary &Clear() override {
        set.Clear();
        return *this;
    };

};

