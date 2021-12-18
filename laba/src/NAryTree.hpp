//
// Created by korna on 30.04.2021.
//
#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <regex>
#include "ArraySequence.hpp"
#include "Stack.hpp"
#include "Pairs.hpp"
#include "Utils.hpp"
#include "GraphIter.hpp"

using namespace std;

template<class T>
class NAryTree : public IEnumerable<T> {
public:
    template<class T1>
    class Node {
    public:
        ArraySequence<T1> values;
        ArraySequence<Node<T1> *> children;
        Node<T1> *parent;

        Node() : values(), children(ArraySequence<Node<T1> *>()), parent(nullptr) {}

        Node(Node<T1> &node) : Node(&node) {}

        explicit Node(Node<T1> *input) : Node() {
            Stack<Node<T1> *> s, s1;
            s.Push(input);
            s1.Push(this);
            while (!s.IsEmpty()) {
                Node<T1> *node = s.Pop();
                Node<T1> *tmp = s1.Pop();
                tmp->values = node->values;
                for (size_t i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL) {
                        tmp->AddChild();
                        s.Push(node->children[i]);
                        s1.Push(tmp->children[i]);
                    }
            }
        }

        explicit Node(T1 data) : Node(data, nullptr, ArraySequence<Node<T1> *>()) {}

        Node(T1 data, Node<T1> *parent) : Node(data, parent, ArraySequence<Node<T1> *>()) {}

        template<size_t children_count>
        Node(T1 data, Node<T1> *parent, Node<T1> *(&children)[children_count]):
                Node(data, parent, ArraySequence<Node<T1> *>(children)) {}

        Node(T1 data, Node<T1> *parent, ArraySequence<Node<T1> *> children) :
                values(data), parent(parent), children(children) {}

//        Node(TKey value, Node<TKey> *parent, ArraySequence<Node<TKey> *> children) :
//                value(value), parent(parent), children(children) {}
        template<typename T2>
        T1 Reduce(function<T1(T2, T1)> f, T1 c) {
            if (f == nullptr)
                throw invalid_argument("mapper is NULL");
            T res = c;
            Stack<Node<T> *> s;
            s.Push(this);
            while (!s.IsEmpty()) {
                Node<T> *node = s.Pop();
                res = Utils::Reduce(node->values, f, res);
                for (size_t i = 0; i < node->ChildrenCount(); ++i)
                    if (node->children[i] != NULL)
                        s.Push(node->children[i]);

            }
            return res;
        }


        size_t ChildrenCount() {
            return children.Count();
        }

        bool IsLeaf() {
            return children.Count() == 0;
        }

        Node<T1> *GetLastChild() {
            return children.GetLast();
        }

        void AddChild(Node<T1> *child) {
            child->parent = this;
            children.Append(child);
        }

        void AddChild() {
            Node<T1> *child = new Node<T1>();
            child->parent = this;
            children.Add(child);
        }

        ~Node() {
            for (size_t i = 0; i < children.Count(); ++i) {
                delete children[i];
            }
        }
    };

protected:
    class Iterator : public GraphIter<T> {
    private:
        Node<T> *current;
        size_t i{};
        size_t j{};
        Stack<Node<T> *> fStack;
        LinkedList<Node<T> *> bList;
    public:
        explicit Iterator(const NAryTree<T> &it, size_t pos = 0) : GraphIter<T>::GraphIter(it, -1), i(),
                                                                   fStack{it.root}, bList() {
            *this += (pos + 1);
        }

        Iterator(const Iterator &other) : GraphIter<T>(other.iterable) { *this = other; }

        T &operator*() const override { return current->values[i]; }

        T *operator->() const override { return &current->values[i]; }

        Iterator &operator++() override {
            if (i + 1 < current->values.Count()) {
                i++;
            } else if ((long) j > 0) {
                current = bList[--j];
            } else {
                j = 0;
                i = 0;
                do {
                    if (current != nullptr)
                        bList.AddFirst(current);
                    current = fStack.Pop();

                    for (size_t k = 0; k < current->ChildrenCount(); ++k)
                        if (current->children[k] != NULL)
                            fStack.Push(current->children[k]);
                } while (current->values.Count() != 0);
            }
            ++this->pos;
            return *this;
        }

        Iterator &operator--() override {
            if (i - 1 >= 0) {
                i--;
            } else {
//                fStack.Push(current);
                current = bList[++j];
                i = current->values.Count() - 1;
            }
            --this->pos;
            return *this;
        }

        Iterator &operator=(const Iterator &list) {
            if (&this->iterable != &list.iterable)
                throw invalid_argument("Iterables must be equal");
            if (this != &list) {
                this->indexes = list.indexes;
                this->pos = list.pos;
                this->current = list.current;
            }
            return *this;
        }
    };

public:
    Iter<T> begin() const override { return Iter<T>(new Iterator(*this)); }

    Iter<T> end() const override {
        return Iter<T>(new Iterator(*this, this->Count() > 0 ? this->Count() : 0));
    }

    Node<T> *GetNode(initializer_list<size_t> indexes) {
        Node<T> *res = root;
        for (size_t item: indexes)
            res = res->children[item];
        return res;
    }

    template<size_t N>
    Node<T> *GetNode(const size_t (&indexes)[N]) {
        Node<T> *res = root;
        for (size_t i = 0; i < N; ++i) {
            res = res->children[indexes[i]];
        }
        return res;
    }

    template<size_t N>
    ArraySequence<Node<T> *> GetPath(const size_t (&indexes)[N]) {
        Node<T> *tmp = root;
        ArraySequence<Node<T> *> res;
        for (size_t i = 0; i < N; ++i) {
            res.Append(tmp);
            tmp = tmp->children[indexes[i]];
        }
        return res;
    }


    size_t n{};
    Node<T> *root;
    size_t count{};

public:
    NAryTree() : NAryTree(2) {}

    explicit NAryTree(size_t n) : NAryTree(new Node<T>(), n, 0) {}

    explicit NAryTree(Node<T> *root, size_t count) : n(root->ChildrenCount()), root(root), count(count) {}

    NAryTree(NAryTree<T> &tree) : n(tree.n), root(new Node<T>(tree.root)), count(tree.count) {}

    NAryTree(Node<T> *root, size_t n, size_t count) : n(n), root(root), count(count) {}

    NAryTree(const string &str, const string &br) {
        count = 0;
        regex word_regex(R"(([^\dK])((\d)+|(K))([^\dK]))");
        auto words_begin = sregex_iterator(br.begin(), br.end(), word_regex);
        auto words_end = sregex_iterator();
        const size_t length = distance(words_begin, words_end);
        n = length - 1;
        string check;
        string brackets;
        size_t *indexes = new size_t[length]();
        int j = 0;
        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;
            string match_str = match.str();
            size_t num;
            if (match_str[1] == 'K')
                num = length;
            else {
                stringstream s(match_str.substr(1, match_str.size() - 2));
                s >> num;
            }
            num -= 1;
            if (num >= length)
                throw runtime_error("wrong input");
            indexes[j] = num;
            brackets[num * 2] = match_str[0];
            brackets[num * 2 + 1] = match_str[match_str.size() - 1];
            ++j;
        }
        check = "";
        string openBr;
        string closeBr;
        string rootBr = string(1, brackets[2 * n]) + string(1, brackets[2 * n + 1]);
        for (int i = 0; i < n; ++i) {
            openBr += string(1, brackets[2 * i]);
            closeBr += string(1, brackets[2 * i + 1]);
        }
        size_t len = str.length();

        Stack<char> bracketSequence;
        root = new Node<T>();
        Node<T> *node = root;
        size_t tmp;
        for (int i = 0; i < len; ++i) {
            size_t found1 = openBr.find(str[i]);
            size_t found2 = closeBr.find(str[i]);
            if (found1 != string::npos) {
                bracketSequence.Push(str[i]);
                while (node->ChildrenCount() <= found1)
                    node->AddChild();
                node = node->children[found1];
            } else if (rootBr[0] == str[i]) {
                bracketSequence.Push(str[i]);
                tmp = i;
            } else if (found2 != string::npos) {
                if (bracketSequence.Pop() != openBr[found2])
                    throw std::runtime_error("Wrong input");
                node = node->parent;
            } else if (rootBr[1] == str[i]) {
                if (bracketSequence.Pop() != rootBr[0])
                    throw std::runtime_error("Wrong input");
                try {
                    stringstream ss(str.substr(tmp + 1, i));
                    T d;
                    ss >> node->values[0];
                    while (ss >> d) {
                        count++;
                        node->values.Append(d);
                    }

                }
                catch (const std::exception &) {
                    throw std::runtime_error("Wrong input type");
                }
            }
        }
        delete[] indexes;
        if (!bracketSequence.IsEmpty())
            throw std::runtime_error("Wrong input");
    }

    NAryTree &Insert(size_t at, initializer_list<size_t> indexes, T k) {
        GetNode(indexes)->values.InsertAt(at, k);
        return *this;
    }

    NAryTree &Remove(size_t at, initializer_list<size_t> indexes) {
        GetNode(indexes)->values.RemoveAt(at);
        return *this;
    }

    size_t GetN() { return n; }

    NAryTree<T> &operator=(const NAryTree<T> &list) {
        if (this != &list) {
            this->~NAryTree();
            n = list.n;
            count = list.count;
            root = new Node<T>(*list.root);
        }
        return *this;
    }

    [[nodiscard]] size_t Count() const { return count; }

    string Order() {
        return Order("{K}(2)[1]<3>d4b\\5/");
    }

    string Order(const string &str) {
        regex word_regex(R"(([^\dK])((\d)+|(K))([^\dK]))");
        auto words_begin = sregex_iterator(str.begin(), str.end(), word_regex);
        auto words_end = sregex_iterator();
        size_t length = distance(words_begin, words_end);
        if (!regex_search(str, regex(R"(^(([^\dK])((\d)+|(K))([^\dK]))+$)")))
            throw runtime_error("wrong input");
//        cout << length << endl;
        string brackets;
        size_t *indexes = new size_t[length]();
        int j = 0;
        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;
            string match_str = match.str();
            size_t num;
            if (match_str[1] == 'K')
                num = length;
            else {
                stringstream s(match_str.substr(1, match_str.size() - 2));
                s >> num;
            }
            num -= 1;
            if (num >= length)
                throw runtime_error("wrong input");
            indexes[j] = num;
            brackets[num * 2] = match_str[0];
            brackets[num * 2 + 1] = match_str[match_str.size() - 1];
            ++j;
        }
        if (root == NULL)
            throw runtime_error("Root is NULL");
        stringstream buffer;
        function<void(Node<T> *, long long)> VisitNode = [&](Node<T> *node, long long br) {
            if (br != -1)
                buffer << brackets[indexes[br] * 2];
            for (size_t i = 0; i < length; ++i)
                if (indexes[i] == length - 1) {
                    buffer << brackets[2 * length - 2];
                    for (size_t k = 0; k < node->values.Count(); ++k) {
                        buffer << node->values[k];
                        if (k != node->values.Count() - 1)
                            buffer << " ";
                    }
                    buffer << brackets[2 * length - 1];
                } else if (indexes[i] < node->ChildrenCount())
                    VisitNode(node->children[indexes[i]], i);
            if (br != -1)
                buffer << brackets[indexes[br] * 2 + 1];
        };
        VisitNode(root, -1);
        delete[] indexes;
        return buffer.str();
    }


//    NAryTree<T> Subtree(initializer_list<size_t> indexes) {
//        return NAryTree<T>(new Node(GetNode(indexes)));
//    }
//
//    template<size_t N>
//    NAryTree<T> Subtree(const size_t (&indexes)[N]) {
//        return NAryTree<T>(new Node(GetNode(indexes)));
//    }

    ~NAryTree() {
        delete root;
    }
};