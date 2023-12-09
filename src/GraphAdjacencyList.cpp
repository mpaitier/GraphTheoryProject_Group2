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

bool GraphAdjacencyList::isEdge(int v, int w){
    for(int i=0; i<adjacencyList[v].size(); i++){
        if(adjacencyList[v][i] == w){
            return true;
        }
    }
    return false;
}

int GraphAdjacencyList::InDegree(int v, vector<int> V1){
    int count = 0;
    for(int i=0; i<V1.size(); i++){
        if(isEdge(v, V1[i])){
            count++;
        }
    }
    return count;

}

int GraphAdjacencyList::OutDegree(int v, vector<int> V2){
    int count = 0;
    for(int i=0; i<V2.size(); i++){
        if(isEdge(v, V2[i])){
            count++;
        }
    }
    return count;

}
