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
        LinkedList<Edge *> edges{};

        Node() = default;

        Node(TValue value, TWeight weight) : value(value), weight(weight), edges{} {

        }

        Node(const Node &) = default;

        Edge *AddAdjacent(Node *node) {
            Edge *edge = new Edge(TWeight(), this, node);
            edges.Add(edge);
            return edge;
        }

        void AddAdjacent(Edge *edge) {
            edges.Add(edge);
        }

        bool IsAdjacent(Node *other) {
            for (auto el: edges)
                if (el->GetAdjacent(other) == this)
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


    Graph(int count, int num) : Graph(size_t(count), size_t(num)) {}

    explicit Graph(size_t count, size_t num = 0, bool directed = true, bool nodeWeighted = false,
                   bool edgeWeighted = false) :
            nodes(count), directed(directed), nodeWeighted(nodeWeighted), edgeWeighted(edgeWeighted) {
        for (size_t i = 0; i < nodes.Count(); ++i) {
            nodes[i] = new Node();
            if constexpr(std::is_same<TValue, int>::value) {
                nodes[i]->value = i;
            }
        }
        size_t maxEdges = directed ? count * count : count * (count - 1) / 2;
        if (maxEdges < num)
            throw invalid_argument("Too many nodes to generate");
        for (size_t k = 0; k < num; ++k) {
            auto i = Random<size_t>(0, count - 1), j = Random<size_t>(0, count - 1);
//            if(i!=j)
//                cout << endl;
            if (!nodes[i]->IsAdjacent(nodes[j])) {
                TWeight rnd = Random<TWeight>();
                Edge *edge;
                if (nodes[i]->IsAdjacent(nodes[j]))
                    edge = nodes[j]->AddAdjacent(nodes[i]);
                else
                    edge = nodes[i]->AddAdjacent(nodes[j]);
                edge->weight = rnd;
                if (!directed && i!= j)
                    nodes[j]->AddAdjacent(edge);
            } else {
                --k;
            }
        }
    }

    string GraphvizPrint() {
        stringstream ss;
        Set<Edge *> passed;
        ss << (directed ? "digraph" : "graph") << '{' << endl;
        for (auto node: nodes) {
            ss << '"' << node << '"' << "[label=" << node->value;
            if (nodeWeighted)
                ss << ", xlabel=" << node->weight;
            ss << "];" << endl;
            for (auto edge: node->edges) {
                if (!passed.Contains(edge)) {
                    ss << '"' << node << '"' << (directed ? "->" : "--") << '"' << edge->GetAdjacent(node) << '"';
                    if (edgeWeighted)
                        ss << "[label=\" " << edge->weight << " \"]";
                    ss << ';' << endl;
                    passed.Add(edge);
                }
            }
        }
        ss << '}' << endl;
        return ss.str();
    }

    ~Graph() {
        for (auto node: nodes) {
            for (auto edge: node->edges) {
                    LinkedList<Edge *> *edges = &edge->GetAdjacent(node)->edges;
                    if (edges->Contains(edge) && edge->GetAdjacent(node) != node)
                        edges->Remove(edge);
                    delete edge;
            }
            delete node;
        }
    }
};
