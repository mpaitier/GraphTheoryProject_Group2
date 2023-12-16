#ifndef TD3_GRAPHADJACENCYLIST_H
#define TD3_GRAPHADJACENCYLIST_H

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class GraphAdjacencyList {
public:
    /* <------# Constructor #------> */
    GraphAdjacencyList(int vertices);

    /* <------# Attributes #------> */
    int V;  //number of vertices
    vector<vector<int>> adjacencyList; //adjacency list

    /* <------# Methods #------> */
    void addEdge(int v, int w); // add an edge between the vertices v and w
    bool isEdge(int v, int w); // check if there is an edge between the vertices v and w

    void printGraph();  // print the graph

    int degree(int v); // compute the degree of the vertex v
    vector<int> allDegrees(); // compute the degree of all the vertices
    int InOutDegree(int v, vector<int> V1); // compute the in or out degrees of the vertex v
};

/* <------# Functions #------> */
int calculEdgeCommun(GraphAdjacencyList G, vector<vector<int>> subgraphs);

void WriteToFile(const std::string& directory, const string& filename, const vector<int>& v1, const vector<int>& v2, int commonEdges);

#endif //TD3_GRAPHADJACENCYLIST_H
