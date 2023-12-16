#include "LocalSearchHeuristic.h"

vector<vector<int>> LocalSearch(GraphAdjacencyList &graph) {
/*
 * INPUT : a graph
 * OUTPUT : two subgraphs V1 and V2
 * FUNCTION : apply the local search heuristic to the graph : for each vertex V1[X1] of V1, we check if there is a vertex V2[X2] of V2 such that :
 * if the total in degrees of V1[X1] and V2[X2] is smaller than the total out degrees of V1[X1] and V2[X2], we swap the two vertices.
 */

    // create two subgraphs V1 and V2, result of the constructive heuristic
    vector<vector<int>> subgraphs = ConstructiveHeuristic(graph);
    vector<int> V1 = subgraphs[0];
    vector<int> V2 = subgraphs[1];

    // initialize the in and out degrees of the vertices
    int InDegreeV1 = 0;
    int InDegreeV2 = 0;
    int InDegrees = 0;

    int OutDegreeV1 = 0;
    int OutDegreeV2 = 0;
    int OutDegrees = 0;

    // initialize the number of common edges
    int commun = 0;

    for(int X1 = 0; X1 < V1.size(); X1++){

        // compute the in and out degrees of the vertex V1[X1]
        InDegreeV1 = graph.InOutDegree(V1[X1],V1);
        OutDegreeV1 = graph.InOutDegree(V1[X1],V2);

        for (int X2 = 0; X2 < V2.size(); X2++) {

            // check if there is an edge between the two vertices
            if(graph.isEdge(V1[X1], V2[X2])){
                commun = 1;
            }
            else{
                commun = 0;
            }

            // compute the in and out degrees of the vertex V2[X2]
            OutDegreeV2 = graph.InOutDegree(V2[X2],V1);
            InDegreeV2 = graph.InOutDegree(V2[X2],V2);

            // compute the total in degrees and the total out degrees of the two vertices V1[X1] and V2[X2]
            InDegrees = InDegreeV1 + InDegreeV2;
            OutDegrees = OutDegreeV1 + OutDegreeV2 - commun;

            // if the total in degrees of V1[X1] and V2[X2] is smaller than the total out degrees, then ...
            if ( InDegrees < OutDegrees) {

                // swap the two vertices
                int temp = V1[X1];
                V1[X1] = V2[X2];
                V2[X2] = temp;
            }

        }
    }
    // return the two subgraphs V1 and V2
    vector<vector<int>> result;
    result.push_back(V1);
    result.push_back(V2);

    return result;
}