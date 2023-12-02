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

    int degree(int v); // calcul du degré d'un sommet
};


#endif //TD3_GRAPHADJACENCYLIST_H
