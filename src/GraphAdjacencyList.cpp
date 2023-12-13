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

int calculEdgeCommun(GraphAdjacencyList G, vector<vector<int>> subgraphs){
    vector<int> V1 = subgraphs[0];
    vector<int> V2 = subgraphs[1];
    int som = 0;
    for(int i=0; i<V1.size(); i++){
        for(const int &neighbor : G.adjacencyList[V1[i]]){
            for(int j=0; j<V2.size(); j++){
                if(neighbor == V2[j]){
                    som ++;
                }
            }
        }
    }
    return som;
}

