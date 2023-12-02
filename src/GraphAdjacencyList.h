#ifndef TD3_GRAPHADJACENCYLIST_H
#define TD3_GRAPHADJACENCYLIST_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class GraphAdjacencyList {
public:
    GraphAdjacencyList(int vertices);
    void addEdge(int v, int w);
    void printGraph();
    int V;  //nbr de sommet
    vector<vector<int>> adjacencyList;
};


#endif //TD3_GRAPHADJACENCYLIST_H
