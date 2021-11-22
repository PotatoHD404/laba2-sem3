//
// Created by PotatoHD on 22.11.2021.
//

#pragma once

#include <any>
#include <map>


template<template<typename> class ICollection, typename T>
class CollectionFactory {
public:
    std::map<string, std::function<ICollection<T> &&>> arr;

//    class
//
//    template<template<typename> class Child>
//    CollectionFactory():New([]() -> ICollection<T> && {
//        auto res = Child<T>();
//        return move(res);
//    }) {}

    template<class Child>
    void Register(){

    };
};
