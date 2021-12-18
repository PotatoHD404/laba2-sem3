//
// Created by PotatoHD on 28.11.2021.
//

#pragma once

#include "ICollection.hpp"
#include "Pairs.hpp"

template<typename TKey, typename TValue>
class IDictionary : public ICollection<const KeyValue<TKey, TValue>> {
public:
    IDictionary &Add(KeyValue<TKey, TValue>) override = 0;

    IDictionary &Remove(KeyValue<TKey, TValue>) override = 0;

    virtual KeyValue<TKey, TValue> &Get(TKey key) const = 0;

    virtual TValue &operator[](TKey key) const = 0;

    virtual IDictionary &Add(TKey key, TValue value) = 0;

    virtual IDictionary &Remove(TKey key) = 0;
};
