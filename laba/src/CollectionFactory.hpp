//
// Created by PotatoHD on 22.11.2021.
//

#pragma once

template<template<typename> class Base, class T>
class CollectionFactory {
    const std::function<Base<T> &&> New;


    template<template<typename> class Child>
    CollectionFactory():New([]() -> Base<T> && {
        auto res = Child<T>();
        return move(res);
    }) {}
};
