//
// Created by PotatoHD on 28.11.2021.
//

#pragma once

#include "Set.hpp"
#include "Pairs.hpp"
#include "IDictionary.hpp"
#include "MapCollection.hpp"

template<typename TKey, typename TValue>
class Dictionary : public IDictionary<TKey, TValue> {
private:
    using iCollection = ICollection<KeyValue<TKey, TValue>>;
    using keyValue = KeyValue<TKey, TValue>;
    Set<keyValue> set;

public:
    using KeySet = MapCollection<const TKey, const keyValue>;
    using ValueSet = MapCollection<TValue, const keyValue>;
    const KeySet keys{this, [](const keyValue &keyValue) -> const TKey & {
        return keyValue.GetKey();
    }};
    const ValueSet values{this, [](const keyValue &keyValue) -> TValue & {
        return keyValue.GetValue();
    }};


    keyValue &Get(TKey key) const override {
        auto pair = keyValue(key);
        auto node = set.Find(pair);
        if (node == nullptr)
            throw invalid_argument("Key was not found");
        for (keyValue &el: node->values) {
            if (el == pair) {
                return el;
            }
        }
        throw invalid_argument("Key was not found");
    }

    TValue &operator[](TKey key) const override {
        return Get(key).GetValue();
    }

    Iter<const keyValue> begin() const override { return set.begin(); }

    Iter<const keyValue> end() const override { return set.end(); }

    [[nodiscard]] size_t Count() const override { return set.Count(); }

    Dictionary &Add(keyValue item) override {
        set.Add(item);
        return *this;
    }

    Dictionary &Remove(keyValue item) override {
        set.Remove(item);
        return *this;
    }

    Dictionary &Clear() override {
        set.Clear();
        return *this;
    };

    Dictionary &Add(TKey key, TValue value) override {
        this->Add(keyValue(key, value));
        return *this;
    }

    Dictionary &Remove(TKey key) override {
        this->Remove(keyValue(key));
        return *this;
    }

    bool Contains(keyValue pair) const override {
        return set.Contains(pair);
    }

    bool Contains(TKey key) const {
        return Contains(keyValue(key));
    }

    Dictionary &operator=(const Dictionary &) = delete;
};


