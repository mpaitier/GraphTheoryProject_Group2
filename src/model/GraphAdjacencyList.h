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
    vector<int> allDegrees();

    // Besoin pour le local search
    int InOutDegree(int v, vector<int> V1); // calcule le nombre d'arrêtes que le sommet à avec les autres sommets de son sous-ensemble V1 ou V2

    bool isEdge(int v, int w); // vérifie si il y a une arrête entre les sommets v et w
};

int calculEdgeCommun(GraphAdjacencyList G, vector<vector<int>> subgraphs);

#endif //TD3_GRAPHADJACENCYLIST_H