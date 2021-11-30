//
// Created by korna on 20.03.2021.
//
#pragma once

#include <iostream>
#include <cstring>
#include "IList.hpp"
#include "GraphIter.hpp"
#include "IterImpl.hpp"


using namespace std;

template<typename T>
class LinkedList : public IList<T> {
private:
    class Node;


    mutable Node *head, *tail;
    size_t length;

    class Node {
    public:
        Node *next;
        Node *prev;
        T data;


        Node() : Node(T(), nullptr, nullptr) {}

        explicit Node(T data) : Node(data, nullptr, nullptr) {}

        Node(T data, Node *next, Node *prev) : next(next), prev(prev), data(data) {}
    };

    Node *GetNode(size_t index) const {
        if (index == Count())
            return nullptr;
        if (index == Count() - 1)
            return tail;
        Node *res = head;
        for (size_t i = 0; i < index; i++) {
            res = res->next;
        }
        return res;
    }

    class Iterator : public GraphIter<T> {
    private:
        Node *current;
    public:

        explicit Iterator(const LinkedList<T> *it, size_t pos = 0) : GraphIter<T>(it, pos), current(it->head) {
            if (it->Count() == pos) {
                current = nullptr;
            } else if (pos <= it->Count() / 2)
                *this += pos;
            else {
                current = it->tail;
                *this -= pos - 1;
            }
        }

        Iterator(const Iterator &other) : GraphIter<T>(other.it) { *this = other; }


        T &operator*() const override { return current->data; }

        T *operator->() const override { return &current->data; }

//        using ListIter<TKey>::ListIter;
        Iterator &operator++() override {
            current = current->next;
            ++this->pos;
            return *this;
        }

        Iterator &operator--() override {
            if (current == nullptr && this->pos == this->it->Count())
                current = ((LinkedList<T> *) this->it)->tail;
            else
                current = current->prev;
            --this->pos;
            return *this;
        }


        Iterator &operator=(const Iterator &list) {
            if (this != &list) {
                this->it = list.it;
                this->pos = list.pos;
                this->current = list.current;
            }
            return *this;
        }
    };

public:
    Iter<T> begin() const override { return Iter<T>(new Iterator(this)); }

    Iter<T> end() const override {
        return Iter<T>(new Iterator(this, this->Count() > 0 ? this->Count() : 0));
    }
    //Creation of the object

    LinkedList() : head(nullptr), tail(nullptr), length() {}

    explicit LinkedList(size_t count) : LinkedList() {
        if ((long) count < 0)
            throw out_of_range("count < 0");
        if (count > 0) {
            Node *curr = new Node();
            head = curr;
            for (size_t i = 1; i < count; ++i) {
                head->next = new Node();
                head->next->prev = head;
                head = head->next;
            }
            tail = head;
            head = curr;
            length = count;
        }
    }

    LinkedList(T *items, size_t count) : LinkedList() {
        if ((long) count < 0)
            throw out_of_range("count < 0");
        if (items == nullptr)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            head = new Node(items[0]);
            Node *prev = head;
            for (size_t i = 1; i < count; ++i) {
                prev->next = new Node(items[i]);
                prev->next->prev = prev;
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    LinkedList(const LinkedList<T> &list) : LinkedList() {
        length = 0;
        *this = list;
    }

    //Decomposition

    T &GetFirst() const {
        if (!head)
            throw out_of_range("");
        return head->data;
    }

    T &GetLast() const {
        if (!tail)
            throw out_of_range("");
        return tail->data;
    }

    T &Get(size_t index) const override {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        if (index == 0)
            return GetFirst();
        if (index == length - 1)
            return GetLast();
        return GetNode(index)->data;
    }

    LinkedList<T> &Clear() override { throw NotImplemented("", "in LinkedList Clear"); };

//    bool operator==(const IList<TKey> &list) override {
//        if (dynamic_cast<const LinkedList<TKey> *>(&list) != nullptr) {
//            auto castedList = dynamic_cast<const LinkedList<TKey> &>(list);
//            if (this->Count() != castedList.Count())
//                return false;
//            auto head1 = this->head;
//            auto head2 = castedList.head;
//            while (head1) {
//                if (head1->data != head2->data)
//                    return false;
//                head1 = head1->next;
//                head2 = head2->next;
//            }
//            return true;
//        }
//        if (this->Count() != list.Count())
//            return false;
//        int i = 0;
//        for (TKey el: *this) {
//            if (el != list[i])
//                return false;
//            i++;
//        }
//        return true;
//    }


    LinkedList<T> GetSubList(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= length)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= length)
            throw range_error("endIndex >= length");
        LinkedList<T> res;
        Node *tmp = GetNode(startIndex);
        for (size_t i = startIndex; i < endIndex + 1; ++i) {
            res.Add(tmp->data);
            tmp = tmp->next;
        }
        return res;
    }

    [[nodiscard]] size_t Count() const override {
        return length;
    }

    T &operator[](size_t index) const override { return Get(index); }

    //Operations

    LinkedList<T> &Add(T item) override {
        Node *tmp = new Node(item);
        if (head == nullptr)
            head = tmp;
        else
            tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
        ++length;
        return *this;
    }

    LinkedList<T> &AddFirst(T item) {
        Node *tmp = new Node(item);
        if (head == nullptr) {
            head = tmp;
            tail = tmp;
        } else {
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
        }
        ++length;
        return *this;
    }

    T RemoveLast() {
        if (length < 1)
            throw range_error("length = 0");
        if (length == 1) {
            return this->RemoveFirst();
        }
        T data = tail->data;
        tail = tail->prev;

        delete tail->next;
        tail->next = nullptr;
        --length;
        return data;
    }

    T RemoveFirst() {
        if (length == 0)
            throw range_error("No elements to remove");
        T data = head->data;
        if (length == 1) {
            delete head;
            tail = nullptr;
            head = nullptr;
        } else {
            Node *prev = head;
            head = head->next;
            delete prev;
            head->prev = nullptr;
        }
        --length;

        return data;
    }

    LinkedList<T> &Insert(size_t index, T item) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1) {
            return this->Add(item);
        } else if (index == 0) {

            return this->AddFirst(item);;
        }


        Node *tmp = new Node(item);
        Node *prev = GetNode(index - 1);
        Node *next = prev->next;
        prev->next = tmp;
        next->prev = tmp;
        tmp->next = next;
        ++length;
        return *this;
    }

    T RemoveAt(size_t index) override {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1)
            return this->RemoveLast();
        else if (index == 0)
            return this->RemoveFirst();

        Node *prev = GetNode(index - 1);
        Node *next = (prev->next)->next;
        T data = prev->next->data;
        delete prev->next;
        prev->next = next;
        next->prev = prev;
        --length;
        return data;
    }

    LinkedList<T> Concat(LinkedList<T> &list) {
        LinkedList<T> res;
        for (size_t i = 0; i < length; ++i) {
            res.Add(this->Get(i));
        }
        for (size_t i = 0; i < list.length; ++i) {
            res.Add(list[i]);
        }
        return res;
    }

    LinkedList<T> &operator=(const LinkedList<T> &list) {
        if (&list != this) {
            while (length)
                RemoveFirst();
            if (list.Count() > 0) {
                Node *tmp = list.head;
                head = new Node(tmp->data);
                Node *prev = head;
                tmp = tmp->next;
                while (tmp != nullptr) {
                    prev->next = new Node(tmp->data);
                    prev->next->prev = prev;
                    prev = prev->next;
                    tmp = tmp->next;
                }
                tail = prev;
                length = list.Count();
            } else {
                head = nullptr;
                tail = nullptr;
                length = 0;
            }
        }
        return *this;
    }

    //Termination

    ~LinkedList() {
        while (length)
            RemoveFirst();
    }
};
