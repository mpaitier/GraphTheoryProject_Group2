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
        cout << "Sommet " << i << " : ";
        for (const int &neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

int GraphAdjacencyList::degree(int v) {
    return adjacencyList[v].size();
}

vector<int> GraphAdjacencyList::allDegrees(){
    vector<int> tab;
    for(int i=0; i<V; i++){
        tab.push_back(degree(i));
    }
    return tab;
}

