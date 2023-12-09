#include "LocalSearchHeuristic.h"

void LocalSearch(GraphAdjacencyList &graph, vector<int> &V1, vector<int> &V2) {
    int commun = 0;
    bool change = true;

    while(change){
        change = false;
        for(int X1 = 0; X1 < V1.size(); X1++){

            for (int X2 = 0; X2 < V2.size(); X2++) {

                if(graph.isEdge(V1[X1], V2[X2])){
                    commun = 1;
                }
                else{
                    commun = 0;
                }

                if ( (graph.InDegree(X1,V1)) + graph.InDegree(X2,V1) < graph.OutDegree(X1,V2) + graph.OutDegree(X2,V1) - commun) {
                    int temp = V1[X1];
                    V1[X1] = V2[X2];
                    V2[X2] = temp;

                    change = true;
                }

            }
        }
    }
}