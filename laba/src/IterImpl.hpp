//
// Created by kmv026 on 13.10.2021.
//
#pragma once

template<typename Interface>
class IterImpl {
private:
    Interface *storage;

    Interface *(*copy)(Interface &);

public:
    using T = typename Interface::type;
    using difference_type = typename Interface::difference_type;
    using value_type = typename Interface::value_type;
    using reference = typename Interface::reference;
    using pointer = typename Interface::pointer;
    using iterator_category = typename Interface::iterator_category;
public:
    [[nodiscard]] size_t GetPos() const {
        return storage->GetPos();
    }

    friend bool operator==(const IterImpl &a, const IterImpl &b) {
        return a.storage->Equals(*b.storage);
    }

    friend bool operator==(const IterImpl &a, const BaseIter<T> &b) {
        return a.storage->Equals(b);
    }

    friend bool operator!=(const IterImpl &a, const IterImpl &b) {
        return !a.storage->Equals(*b.storage);
    }

    IterImpl(const IterImpl &iter) : storage(iter.copy(*iter.storage)), copy(iter.copy) {}

    template<class ConcreteType>
    [[maybe_unused]] explicit IterImpl(ConcreteType *it)
            : storage(it),
              copy([](Interface &strg) -> Interface * {
                  return new ConcreteType(dynamic_cast<ConcreteType &>(strg));
              }) {}

    virtual T *operator->() { return storage->operator->(); }

    virtual T &operator*() const { return **storage; }

    // Prefix increment
    virtual IterImpl &operator++() {
        ++(*storage);
        return *this;
    }

    // Postfix increment
    virtual IterImpl operator++(int) { // NOLINT(cert-dcl21-cpp)
        IterImpl tmp = IterImpl(*this);
        ++(*this);
        return tmp;
    }
    // Prefix increment

    virtual IterImpl &operator--() {
        --(*storage);
        return *this;
    }

    virtual IterImpl operator--(int) { // NOLINT(cert-dcl21-cpp)
        IterImpl tmp = IterImpl(*this);
        --(*this);
        return tmp;
    }

    virtual IterImpl &operator+=(size_t num) {
        *this->storage += num;
        return *this;
    };

    virtual IterImpl &operator-=(size_t num) {
        *this->storage -= num;
        return *this;
    };

    virtual IterImpl &operator*=(size_t num) {
        *this->storage *= num;
        return *this;
    };

    virtual IterImpl &operator/=(size_t num) {
        *this->storage /= num;
        return *this;
    };

    virtual IterImpl operator+(const IterImpl &b) const {
        auto res = IterImpl(*this);
        res += b.GetPos();
        return res;
    }

    virtual IterImpl operator-(const IterImpl &b) const {
        auto res = IterImpl(*this);
        res -= b.GetPos();
        return res;
    }

    virtual IterImpl operator*(const IterImpl &b) const {
        auto res = IterImpl(*this);
        res *= b.GetPos();
        return res;
    }

    virtual IterImpl operator/(const IterImpl &b) const {
        auto res = IterImpl(*this);
        res /= b.GetPos();
        return res;
    }

    virtual IterImpl operator+(size_t b_pos) const {
        auto res = IterImpl(*this);
        res += b_pos;
        return res;
    }

    virtual IterImpl operator-(size_t b_pos) const {
        auto res = IterImpl(*this);
        res -= b_pos;
        return res;
    }

    virtual IterImpl operator*(size_t b_pos) const {
        auto res = IterImpl(*this);
        res *= b_pos;
        return res;
    }

    virtual IterImpl operator/(size_t b_pos) const {
        auto res = IterImpl(*this);
        res /= b_pos;
        return res;
    }

    virtual bool operator<(size_t b_pos) const {
        return *storage < b_pos;
    }

    virtual bool operator<=(size_t b_pos) const {
        return *storage <= b_pos;
    }

    virtual bool operator>(size_t b_pos) const {
        return *storage > b_pos;
    }

    virtual bool operator>=(size_t b_pos) const {
        return *storage >= b_pos;
    }

    virtual bool operator<(const IterImpl &b) const {
        return *storage < *b.storage;
    }

    virtual bool operator<=(const IterImpl &b) const {
        return *storage <= *b.storage;
    }

    virtual bool operator>(const IterImpl &b) const {
        return *storage > *b.storage;
    }

    virtual bool operator>=(const IterImpl &b) const {
        return *storage >= *b.storage;
    }

    explicit operator int() const { return storage->GetPos(); }

    IterImpl &operator=(const IterImpl &list) {
        if (this != &list) {
            delete storage;
            storage = list.copy(*list.storage);
            copy = list.copy;
        }
        return *this;
    }

    ~IterImpl() {
        delete storage;
    }
};
