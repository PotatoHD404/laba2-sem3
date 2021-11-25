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
//    explicit IEnumerator(Iter<Seq> &it, size_t pos) = 0;

//    IEnumerator(const IEnumerator &other) = 0;
//    virtual Base<Seq> Init() = 0;



    [[nodiscard]] virtual bool Equals(const IterImpl &b) const { return storage->Equals(*b.storage); }

    [[nodiscard]] size_t GetPos() const {
        return storage->GetPos();
    }

    friend bool operator==(const IterImpl &a, const IterImpl &b) {
        return *a.storage == *b.storage;
    }

    friend bool operator!=(const IterImpl &a, const IterImpl &b) {
        return *a.storage != *b.storage;
    }

    IterImpl(const IterImpl &a) : storage(a.copy(*a.storage)), copy(a.copy) {}
//    IterImpl(Interface &a) : storage(a.copy(a.storage)), copy(a.copy) {}

    template<typename ConcreteType>
    [[maybe_unused]] explicit IterImpl(ConcreteType *object)
            : storage(new ConcreteType(*object)),
              copy([](Interface &strg) -> Interface * {
                  return new ConcreteType(dynamic_cast<ConcreteType &>(strg));
              }) {}


    template<typename ConcreteType>
    [[maybe_unused]] explicit IterImpl(ConcreteType &object)
            : IterImpl(&object) {}

    template<typename ConcreteType>
    [[maybe_unused]] explicit IterImpl(ConcreteType &&object)
            : IterImpl(&object) {}

    virtual T *operator->() { return storage->operator->(); }

    virtual T &operator*() const { return **storage; }

//    virtual Seq *operator->() const = 0;

    // Prefix increment
    virtual IterImpl &operator++() {
        ++(*storage);
        return *this;
    }

    // Postfix increment
    virtual IterImpl operator++(int) {
        IterImpl tmp = IterImpl(this->storage);
        ++(*this);
        return tmp;
    }

//    operator int() const
//    {
//        return this->pos;
//    }

    // Prefix increment

    virtual IterImpl &operator--() {
        --(*storage);
        return *this;
    }

    virtual IterImpl operator--(int) { // NOLINT(cert-dcl21-cpp)
        IterImpl tmp = IterImpl(this->storage);
        --(*this);
        return tmp;
    }

    virtual IterImpl &operator+=(size_t num) {
        *this = *this + num;
        return *this;
    };

    virtual IterImpl &operator-=(size_t num) {
        *this = *this - num;
        return *this;
    };

    virtual IterImpl operator-(const IterImpl &b) const {
//        IEnumerator &tmp = RAIter(*this);
        return *storage - *b.storage;
    }

    virtual IterImpl operator-(const size_t &b) const {
        return *storage - b;
    }

//    IEnumerator &operator/(const IEnumerator *b) const override {
//        return new IEnumerable(this->iterable, this->pos / b);
//    }

    virtual IterImpl operator/(const size_t &b) const {
        return *storage / b;
    }

    virtual IterImpl operator+(const IterImpl &b) const {
        return *storage + *b.storage;
    }

    virtual IterImpl operator+(const size_t &b) const {
        return *storage + b;
    }

    virtual bool operator<(const size_t &b) const {
        return *storage < b;
    }

    virtual bool operator<=(const size_t &b) const {
        return *storage <= b;
    }

    virtual bool operator>(const size_t &b) const {
        return *storage > b;
    }

    virtual bool operator>=(const size_t &b) const {
        return *storage >= b;
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

//    Interface *operator->() { return &getter(storage); }

    ~IterImpl() {
        delete storage;
    }
};
