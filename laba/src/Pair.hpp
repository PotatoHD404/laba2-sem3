//
// Created by korna on 07.05.2021.
//

#pragma once

template<typename T1, typename T2>
class Pair {
public:
    mutable T1 first;
    mutable T2 second;

    Pair() = default;

    Pair(T1 first, T2 second) : first(first), second(second) {}

    bool operator==(const Pair &x) const { return first == x.first && second == x.second; }

    bool operator!=(const Pair &x) const {
        return !(x == *this);
    }
};

template<typename TKey, typename TValue>
class KeyValue {
private:
    TKey key;
    mutable TValue value;
public:

    KeyValue() = default;

    KeyValue(TKey key, TValue value) : key(key), value(value) {}

    explicit KeyValue(TKey key) : key(key), value() {}


    KeyValue(const KeyValue &other) : key(other.key), value(other.value) {}

    const TKey &GetKey() const {
        return key;
    }

    TValue &GetValue() const {
        return value;
    }

    bool operator==(const KeyValue &x) const { return key == x.key; }

//    bool Equals(const KeyValue &x) const { return key == x.key && value == x.value; }

    bool operator!=(const KeyValue &x) const {
        return !(*this == x);
    }

    bool operator>(const KeyValue &keyValue) const {
        return this->key > keyValue.key;
    }

    bool operator<(const KeyValue &keyValue) const {
        return this->key < keyValue.key;
    }

    bool operator>=(const KeyValue &keyValue) const {
        return this->key >= keyValue.key;
    }

    bool operator<=(const KeyValue &keyValue) const {
        return this->key <= keyValue.key;
    }

    KeyValue &operator=(const KeyValue &) = default;
};

template<typename TKey, typename TValue>
ostream &operator<<(ostream &out, const KeyValue<TKey, TValue> &x) {
    Utils::Print(out, x.GetKey());
    out << ": ";
    Utils::Print(out, x.GetValue());
    return out;
}