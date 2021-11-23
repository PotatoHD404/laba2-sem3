//
// Created by korna on 03.04.2021.
//
#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"
#include "CollectionFactory.hpp"

//https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly
namespace lab {
    template<typename Derived, typename Base>
    class shared_ptr : public std::shared_ptr<Base> {
    public:

        typedef Base BaseOf;

        explicit shared_ptr(std::shared_ptr<Base> &container) :
                std::shared_ptr<Base>(container) {
        }

        std::shared_ptr<Derived> operator->() {
            return dynamic_cast<Derived *>(this);
        }
    };
}


template<typename T>
class ICollection : public IEnumerable<T> {
private:
    using ptr = std::shared_ptr<ICollection<T>>;
protected:
    template<typename T1>
    const static CollectionFactory<ICollection, T1> factory;
public:
    //Decomposition
    using type = T;

    [[nodiscard]] virtual size_t Count() const = 0;

    virtual bool Contains(T item) {
        for (auto el: *this)
            if (el == item)
                return true;
        return false;
    }

    //Operations
    virtual ptr Clear() = 0;

    virtual ptr Add(T item) = 0;

//    template<typename T1 = T>
//    ICollection<T1> &&New() = 0;

//    template<class T1>
//    virtual ptr New() = 0;

    virtual ptr Copy() = 0;

    virtual T Remove(T item) = 0;

    virtual ~ICollection() = default;
};