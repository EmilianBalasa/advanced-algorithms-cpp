#ifndef GRAPH_H
#define GRAPH_H
#include "LinkedList.h"
#include <vector>
#include <string>
class Graph {
public:
    std::vector<LinkedList<int>*> adj;
    Graph(int n) {
        adj.resize(n, nullptr);
        for (int i = 0; i < n; ++i) adj[i] = new LinkedList<int>();
    }
    void addEdge(int u, int v) {
        adj[u]->push_front(v);
    }
    ~Graph() {
        for (auto l : adj) delete l;
    }
};
#endif