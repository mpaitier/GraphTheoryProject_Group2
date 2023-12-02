#include "GraphAdjacencyList.h"


GraphAdjacencyList::GraphAdjacencyList(int vertices) : V(vertices) {
    adjacencyList.resize(vertices);
}

void GraphAdjacencyList::addEdge(int v, int w) {
    adjacencyList[v].push_back(w);
    adjacencyList[w].push_back(v);
}

void GraphAdjacencyList::printGraph() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Sommet " << i << " : ";
        for (const int &neighbor : adjacencyList[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}