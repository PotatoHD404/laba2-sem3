//
// Created by kmv026 on 19.12.2021.
//

#pragma once

#include "Random.hpp"

template<typename TValue, typename TWeight = TValue>
class Graph {
private:
    class Edge;

    class Node {
    public:
        TValue value{};
        TWeight weight{};
        LinkedList<Edge *> adjacent{};

        Node() = default;

        Node(TValue value, TWeight weight) : value(value), weight(weight), adjacent{} {

        }

        Node(const Node &) = default;

        Edge *AddAdjacent(Node *node) {
            Edge *edge = new Edge(TWeight(), this, node);
            adjacent.Add(edge);
            return edge;
        }

        void AddAdjacent(Edge *edge) {
            adjacent.Add(edge);
        }

        bool IsAdjacent(Node *other) {
            for (auto el: adjacent)
                if (el->GetAdjacent(other) != nullptr)
                    return true;

            return false;
        }

        ~Node() = default;
    };

    class Edge {
    public:
        TWeight weight;
        Node *from;
        Node *to;

        Edge(TWeight weight, Node *from, Node *to) : weight(weight), from(from), to(to) {}

        Edge(const Edge &) = default;

        Node *GetAdjacent(Node *node) {
            if (node == from)
                return to;
            if (node == to)
                return from;
            return nullptr;
        }
    };

    ArraySequence<Node *> nodes{};
    bool directed{};
    bool nodeWeighted{};
    bool edgeWeighted{};
public:

//    Iter<T> begin() const override {}

    Graph() = default;

    explicit Graph(size_t count, bool directed = false, bool nodeWeighted = false, bool edgeWeighted = false) :
            nodes(count), directed(directed), nodeWeighted(nodeWeighted), edgeWeighted(edgeWeighted) {
        for (size_t i = 0; i < nodes.Count(); ++i) {
            nodes[i] = new Node();
            if constexpr(std::is_same<TValue, int>::value) {
                nodes[i]->value = i;
            }
        }
    }

    Graph(int count, int num) : Graph(size_t(count), size_t(num)) {}

    Graph(size_t count, size_t num, bool directed = false, bool nodeWeighted = false, bool edgeWeighted = false) :
            Graph(count, directed, nodeWeighted, edgeWeighted) {
        if (count * count < num)
            throw invalid_argument("Too many nodes to generate");
        for (size_t k = 0; k < num; ++k) {
            auto i = Random<size_t>(0, count - 1), j = Random<size_t>(0, count - 1);
            if (!nodes[i]->IsAdjacent(nodes[j])) {
                TWeight rnd = Random<TWeight>();
                auto edge = nodes[i]->AddAdjacent(nodes[j]);
                edge->weight = rnd;
                if (!directed)
                    nodes[j]->AddAdjacent(edge);
            } else
                --i;
        }
    }

    string GraphvizPrint() {
        stringstream ss;
        for (auto node: nodes) {
            ss << '"' << node << '"' << "[label=" << node->value;
            if (nodeWeighted)
                ss << ", xlabel=" << node->weight;
            ss << "];" << endl;
            for (auto edge: node->adjacent) {
                ss << '"' << node << '"' << "->" << '"' << edge->GetAdjacent(node) << '"';
                if (edgeWeighted)
                    ss << "[label=" << edge->weight << "]";
                ss << ";" << endl;
            }
        }
        return ss.str();
    }

    ~Graph() {
        for (size_t i = 0; i < nodes.Count(); ++i) {
            for (size_t j = 0; j < nodes[i]->adjacent.Count(); ++j) {
                if (nodes[i]->adjacent[j] != nullptr) {
                    delete nodes[i]->adjacent[j];
                    nodes[i]->adjacent[j] = nullptr;
                }
            }
            delete nodes[i];
        }
    }
};
