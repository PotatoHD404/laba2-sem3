//
// Created by PotatoHD on 28.11.2021.
//

#pragma once

#include "ICollection.hpp"
#include "Pair.hpp"

template<typename TKey, typename TValue>
class IDictionary : public ICollection<const KeyValue<TKey, TValue>> {
public:
    IDictionary &Add(KeyValue<TKey, TValue>) override = 0;

    IDictionary &Remove(KeyValue<TKey, TValue>) override = 0;

    virtual IDictionary &Add(TKey key, TValue value) {
        this->Add(KeyValue(key, value));
        return *this;
    }

    virtual TValue &Get(TKey key) const = 0;

    virtual TValue &operator[](TKey key) const = 0;

    virtual IDictionary &Remove(TKey key) {
        this->Remove(KeyValue(key, TValue()));
        return *this;
    }
};
