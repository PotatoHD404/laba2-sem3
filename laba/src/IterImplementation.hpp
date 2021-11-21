//
// Created by kmv026 on 13.10.2021.
//
#pragma once

template<typename Interface>
class Implementation {
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
//    virtual Child<Seq> Init() = 0;



    [[nodiscard]] virtual bool Equals(const Implementation &b) const { return storage->Equals(*b.storage); }

    [[nodiscard]] size_t GetPos() const {
        return storage->GetPos();
    }

    friend bool operator==(const Implementation &a, const Implementation &b) {
        return *a.storage == *b.storage;
    }

    friend bool operator!=(const Implementation &a, const Implementation &b) {
        return *a.storage != *b.storage;
    }

    Implementation(const Implementation &a) : storage(a.copy(*a.storage)), copy(a.copy) {}
//    Implementation(Interface &a) : storage(a.copy(a.storage)), copy(a.copy) {}

    template<typename ConcreteType>
    [[maybe_unused]] explicit Implementation(ConcreteType *object)
            : storage(new ConcreteType(*object)),
              copy([](Interface &strg) -> Interface * {
                  return new ConcreteType(dynamic_cast<ConcreteType &>(strg));
              }) {}


    template<typename ConcreteType>
    [[maybe_unused]] explicit Implementation(ConcreteType &object)
            : Implementation(&object) {}

    template<typename ConcreteType>
    [[maybe_unused]] explicit Implementation(ConcreteType &&object)
            : Implementation(&object) {}

    virtual T *operator->() { return storage->operator->(); }

    virtual T &operator*() const { return **storage; }

//    virtual Seq *operator->() const = 0;

    // Prefix increment
    virtual Implementation &operator++() {
        ++(*storage);
        return *this;
    }

    // Postfix increment
    virtual Implementation operator++(int) {
        Implementation tmp = Implementation(this->storage);
        ++(*this);
        return tmp;
    }

//    operator int() const
//    {
//        return this->pos;
//    }

    // Prefix increment

    virtual Implementation &operator--() {
        --(*storage);
        return *this;
    }

    virtual Implementation operator--(int) { // NOLINT(cert-dcl21-cpp)
        Implementation tmp = Implementation(this->storage);
        --(*this);
        return tmp;
    }

    virtual Implementation &operator+=(size_t num) {
        *this = *this + num;
        return *this;
    };

    virtual Implementation &operator-=(size_t num) {
        *this = *this - num;
        return *this;
    };

    virtual Implementation operator-(const Implementation &b) const {
//        IEnumerator &tmp = RandomAccessIterator(*this);
        return *storage - *b.storage;
    }

    virtual Implementation operator-(const size_t &b) const {
        return *storage - b;
    }

//    IEnumerator &operator/(const IEnumerator *b) const override {
//        return new IEnumerable(this->iterable, this->pos / b);
//    }

    virtual Implementation operator/(const size_t &b) const {
        return *storage / b;
    }

    virtual Implementation operator+(const Implementation &b) const {
        return *storage + *b.storage;
    }

    virtual Implementation operator+(const size_t &b) const {
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

    virtual bool operator<(const Implementation &b) const {
        return *storage < *b.storage;
    }

    virtual bool operator<=(const Implementation &b) const {
        return *storage <= *b.storage;
    }

    virtual bool operator>(const Implementation &b) const {
        return *storage > *b.storage;
    }

    virtual bool operator>=(const Implementation &b) const {
        return *storage >= *b.storage;
    }

    Implementation &operator=(const Implementation &list) {
        if (this != &list) {
            delete storage;
            storage = copy(*list.storage);
            copy = list.copy;
        }
        return *this;
    }

//    Interface *operator->() { return &getter(storage); }

    ~Implementation() { delete storage; }
};
