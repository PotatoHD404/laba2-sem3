//
// Created by korna on 08.05.2021.
//

#pragma once

#include "NAryTree.hpp"
#include "Pair.hpp"
#include "Stack.hpp"

template<typename T>
class BTree : public NAryTree<T> {
private:
    class BNode : public NAryTree<T>::template Node<T> {
    public:
        using NAryTree<T>::template Node<T>::Node;

        BNode *Search(T k) {
            size_t i = FindKey(k);

            if (i < this->values.Count() && this->values[i] == k)
                return this;
            else if (this->IsLeaf())
                return nullptr;

            return this->GetChild(i)->Search(k);

        }

        bool RemoveFromLeaf(size_t idx) {
            if (idx < this->values.Count()) {
                this->values.RemoveAt(idx);
                return true;
            }
            return false;
        }

        bool RemoveFromNonLeaf(size_t idx, size_t _t) {
            T k = this->values[idx];
            if (this->children[idx]->values.Count() >= _t) {
                T pred = GetPred(idx);
                this->values[idx] = pred;
                GetChild(idx)->Remove(pred, _t);
                return true;
            } else if (this->children[idx + 1]->values.Count() >= _t) {
                T next = GetNext(idx);
                this->values[idx] = next;
                GetChild(idx + 1)->Remove(next, _t);
                return true;
            } else {
                Merge(idx);
                GetChild(idx)->Remove(k, _t);
                return true;
            }
        }

        void Fill(size_t idx, size_t _t) {
            if (idx != 0 && GetChild(idx - 1)->values.Count() >= _t)
                BorrowFromPrev(idx);
            else if (idx != this->values.Count() && this->children[idx + 1]->values.Count() >= _t)
                BorrowFromNext(idx);
            else {
                if (idx != this->values.Count())
                    Merge(idx);
                else
                    Merge(idx - 1);
            }
        }

// A function to borrow a key from this->children[idx-1] and insert it
// into GetChild(idx)
        void BorrowFromPrev(size_t idx) {
            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx - 1);

            child->values.AddFirst(T());
//            for (size_t i = child->values.Count() - 1; i >= 0; --i)
//                child->values[i + 1] = child->values[i];

//            if (!child->IsLeaf()) {
////                for (size_t i = child->values.Count(); i >= 0; --i)
////                    child->children[i + 1] = child->children[i];
//
//            }

            child->values.AddFirst(this->values[idx - 1]);

//            if (!child->leaf)
//                child->children[0] = sibling->children[sibling->values.Count()];
            if (!child->IsLeaf())
                this->children.AddFirst(sibling->children[sibling->values.Count()]);


            this->values[idx - 1] = sibling->values.RemoveLast();
        }

// A function to borrow a key from the this->children[idx+1] and place
// it in GetChild(idx)
        void BorrowFromNext(size_t idx) {

            BNode *child = GetChild(idx);
            BNode *sibling = GetChild(idx + 1);

            // this->values[idx] is inserted as the last key in GetChild(idx)
            child->values.Add(this->values[idx]);

            // Sibling's first child is inserted as the last child
            // into GetChild(idx)
            if (!(child->IsLeaf()))
                child->children.Add(sibling->children[0]);

            //The first key from sibling is inserted into this->values[idx]
            this->values[idx] = sibling->values[0];

            // Moving all this->values in sibling one step behind
            sibling->values.RemoveFirst();

            // Moving the child pointers one step behind
            if (!sibling->IsLeaf()) {
//                for (size_t i = 1; i <= sibling->values.Count() + 1; ++i)
//                    sibling->children[i - 1] = sibling->children[i];
                sibling->children.RemoveFirst();
            }

        }

        // A function to get predecessor of this->values[idx]
        T GetPred(size_t idx) {
            // Keep moving to the right most node until we reach a leaf
            BNode *cur = GetChild(idx);
            while (!cur->IsLeaf())
                cur = cur->GetChild(cur->values.Count());

            // Return the last key of the leaf
            return cur->values[cur->values.Count() - 1];
        }

        T GetNext(size_t idx) {
            // Keep moving the left most node starting from this->children[idx+1] until we reach a leaf
            BNode *cur = GetChild(idx + 1);
            while (!cur->IsLeaf())
                cur = cur->GetChild(0);

            // Return the first key of the leaf
            return cur->values[0];
        }


        size_t FindKey(T k) {
            size_t res = 0;
            while (res < this->values.Count() && this->values[res] < k)
                ++res;
            return res;
        }

        bool InsertNonFull(T k, size_t _t) {
            size_t i = FindKey(k);
            if (this->IsLeaf()) {
                if (this->values.Count() == i || (i < this->values.Count() && k != this->values[i])) {
                    this->values.Insert(i, k);
                    return true;
                }
                return false;
            } else {
                if (this->children[i]->values.Count() == 2 * _t - 1) {
                    SplitChild(i, this->GetChild(i), _t);
                    if (this->values[i] < k)
                        i++;
                }
                return this->GetChild(i)->InsertNonFull(k, _t);
            }
        }

        bool Remove(T k, size_t _t) {
            size_t idx = FindKey(k);

            // The key to be removed is present in this node
            if (idx < this->values.Count() && this->values[idx] == k) {

                // If the node is a leaf node - removeFromLeaf is called
                // Otherwise, removeFromNonLeaf function is called
                if (this->IsLeaf()) {
                    return RemoveFromLeaf(idx);
                } else
                    return RemoveFromNonLeaf(idx, _t);
            } else {

                // If this node is a leaf node, then the key is not present in tree
                if (this->IsLeaf()) {
//                    cout << "The key " << k << " is does not exist in the tree\n";
                    return false;
                }

                // The key to be removed is present in the sub-tree rooted with this node
                // The flag indicates whether the key is present in the sub-tree rooted
                // with the last child of this node
                bool flag = idx == this->values.Count();

                // If the child where the key is supposed to exist has less that _t this->values,
                // we fill that child
                if (GetChild(idx)->values.Count() < _t)
                    Fill(idx, _t);

                // If the last child has been merged, it must have merged with the previous
                // child and so we recurse on the (idx-1)th child. Else, we recurse on the
                // (idx)th child which now has atleast _t this->values
                if (flag && idx > this->values.Count())
                    GetChild(idx - 1)->Remove(k, _t);
                else
                    GetChild(idx)->Remove(k, _t);
                return true;
            }
        }

        void Merge(size_t idx) {
            BNode *child = this->GetChild(idx);
            BNode *sibling = this->GetChild(idx + 1);
            child->values.Add(this->values[idx]);
            for (size_t i = 0; i < sibling->values.Count(); ++i)
                child->values.Add(sibling->values[i]);
            if (!child->IsLeaf()) {
                for (size_t i = 0; i <= sibling->values.Count(); ++i)
                    child->children.Add(sibling->children[i]);
            }
//            for (size_t i = idx + 1; i < this->values.Count(); ++i)
//                this->values[i - 1] = this->values[i];
            this->values.RemoveAt(idx);
            this->children.RemoveAt(idx + 1);
            sibling->children.Clear();
            delete sibling;
        }

        void SplitChild(size_t i, BNode *y, size_t _t) {
            BNode *z = new BNode();
//            z->values.Resize(_t - 1);
            for (size_t j = 0; j < _t - 1; j++)
//                z->values[j] = y->values[j + _t];
                z->values.AddFirst(y->values.RemoveLast());

            if (!y->IsLeaf()) {
                for (size_t j = 0; j < _t; j++)
                    z->children.AddFirst(y->children.RemoveLast());
            }

            this->children.Insert(i + 1, z);
            this->values.Insert(i, y->values.RemoveLast());
//            y->values.Resize(_t - 1);
        }

        BNode *GetChild(size_t i) {
            return static_cast<BNode *>(this->children[i]);
        }
    };

    class Iterator : public GraphIter<T> {
    private:
        BNode *current;
        Stack<BNode *> fStack, bStack;
    public:
        explicit Iterator(const NAryTree<T> &it, size_t pos = 0) : ListIter<T>::ListIter(it,
                                                                                         pos),
                                                                   current(it.GetNode(pos)), fStack{current} {}

        Iterator(Iterator &other) : ListIter<T>::ListIter(other.iterable, other.pos),
                                    current(other.current), fStack{current} {}

        Iterator(const LinkedList<T> &it, BNode *current, size_t pos) : ListIter<T>::ListIter(
                it, pos), current(current), fStack{current} {}

        T &operator*() const override { return current->data; }

        T *operator->() override { return &current->data; }

        Iterator &operator++() override {
            current = fStack.Pop();
            bStack.Push(current);

            for (size_t i = 0; i < current->ChildrenCount(); ++i)
                if (current->children[i] != NULL)
                    fStack.Push(current->children[i]);

            ++this->pos;
            return *this;
        }

        Iterator &operator--() override {
            current = bStack.Pop();
            fStack.Push(current);

            --this->pos;
            return *this;
        }

        Iterator &operator=(const Iterator &list) {
            if (this != &list) {
                this->fStack = list.fStack;
                this->bStack = list.bStack;
                this->iterable = list.iterable;
                this->pos = list.pos;
                this->current = list.current;
            }
            return *this;
        }
    };

    size_t t{};

public:
    BTree() : BTree(3) {}

    Iter<T> begin() const override { return Iter<T>(Iterator(*this)); }

    Iter<T> end() const override {
        return Iter<T>(Iterator(*this, this->Count() > 0 ? this->Count() : 0));
    }

    ArraySequence<T> ToArraySequence() {
        ArraySequence<T> res;
        if (this->root == NULL)
            throw runtime_error("Root is NULL");

        function<void(BNode *)> VisitNode = [&](BNode *node) {
            size_t length = node->values.Count();
            for (size_t i = 0; i < length; ++i) {
                if (!node->IsLeaf())
                    VisitNode(node->GetChild(i));
                res.Add(node->values[i]);
            }
            if (!node->IsLeaf())
                VisitNode(node->GetChild(length));
        };
        VisitNode(static_cast<BNode *>(this->root));
        return res;
    }

    BTree &Clear() override {
        delete this->root;
        this->root = new BNode();
        this->count = 0;
        return *this;
    }

    [[nodiscard]] size_t Count() const override {
        return ((NAryTree<T> *) this)->Count();
    }

    BTree<T> &operator=(BTree<T> &&list) noexcept {
        this->~BTree();
        this->n = list.n;
        this->count = list.count;
        t = list.t;
        this->root = new BNode(*static_cast<BNode *>(list.root));
        return *this;
    }

    string AscendingOrder() {
        if (this->root == NULL)
            throw runtime_error("Root is NULL");
        stringstream buffer;
        Stack<Pair<BNode *, size_t>> stack;
        stack.Push(Pair(static_cast<BNode *>(this->root), (size_t) 0));
        size_t length = this->count;
        while (!stack.IsEmpty()) {
            if (!stack.Top().first->IsLeaf()) {
                if (stack.Top().first->ChildrenCount() == stack.Top().second)
                    stack.Pop();
                else {

                    if (stack.Top().second != 0) {
                        buffer << stack.Top().first->values[stack.Top().second - 1];
                        length--;
                        if (length != this->count && length)
                            buffer << " ";
                    }

                    stack.Push(Pair(stack.Top().first->GetChild(stack.Top().second++), (size_t) 0));
                }
            } else {
                size_t len = stack.Top().first->values.Count();
                length -= len;
                for (size_t i = 0; i < len; ++i) {
                    buffer << stack.Top().first->values[i];
                    if (i != len - 1)
                        buffer << " ";
                }
                stack.Pop();
                if (length != this->count && length)
                    buffer << " ";
            }
        }
        return buffer.str();
    }

    explicit BTree(size_t t) : NAryTree<T>(new BNode(), 2 * t, 0), t(t) {}

    BTree &Add(T k) override {
        if (static_cast<BNode *>(this->root)->values.Count() == 2 * t - 1) {
            BNode *s = new BNode();
            s->children.Add(this->root);
            s->SplitChild(0, static_cast<BNode *>(this->root), t);
            size_t i = 0;
            if (s->values[i] < k)
                i++;

            if (s->InsertNonFull(k, t))
                this->count++;
            this->root = s;
        } else {
            if (static_cast<BNode *>(this->root)->InsertNonFull(k, t))
                this->count++;
        }
        return *this;
    }

    T GetMin() {
        BNode *tmp = static_cast<BNode *>(this->root);
        while (!tmp->IsLeaf())
            tmp = static_cast<BNode *>(tmp->children.GetFirst());
        return tmp->values.GetFirst();
    }

    T GetMax() {
        BNode *tmp = static_cast<BNode *>(this->root);
        while (!tmp->IsLeaf())
            tmp = tmp->children.GetLast();
        return tmp->values.GetLast();
    }

    T Pop() {
        T res = GetMin();
        Remove(res);
        return res;
    }

    BTree &Remove(T k) override {

        // Call the remove function for root
        if (static_cast<BNode *>(this->root)->Remove(k, t)) {
            this->count--;
        }

        // If the root node has 0 this->values, make its first child as the new root
        //  if it has a child, otherwise BTree root as NULL
        if (this->root->values.Count() == 0 && !static_cast<BNode *>(this->root)->IsLeaf()) {
            BNode *tmp = static_cast<BNode *>(this->root);
//            if (!static_cast<BNode *>(this->root)->IsLeaf())
            this->root = this->root->children[0];

            // Free the old root
            tmp->children.Clear();
            delete tmp;
        }
        return *this;
    }

    bool Contains(T key) override {
        return static_cast<BNode *>(this->root)->Search(key) != nullptr;
    }

    BTree(BTree<T> &tree) : NAryTree<T>(static_cast<NAryTree<T> &>(tree)), t(tree.t) {}

};

