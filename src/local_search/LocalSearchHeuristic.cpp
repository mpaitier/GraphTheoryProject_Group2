#include "LocalSearchHeuristic.h"

vector<vector<int>> LocalSearch(GraphAdjacencyList &graph) {

    // create two subgraphs V1 and V2, result of the constructive heuristic
    vector<vector<int>> subgraphs = ConstructiveHeuristic(graph);
    vector<int> V1 = subgraphs[0];
    vector<int> V2 = subgraphs[1];

    int InDegreeV1 = 0;
    int InDegreeV2 = 0;
    int InDegrees = 0;

    int OutDegreeV1 = 0;
    int OutDegreeV2 = 0;
    int OutDegrees = 0;

    int commun = 0;
    bool change = true;

    //while(change){
        change = false;
        for(int X1 = 0; X1 < V1.size(); X1++){

            for (int X2 = 0; X2 < V2.size(); X2++) {

                if(graph.isEdge(V1[X1], V2[X2])){
                    commun = 1;
                }
                else{
                    commun = 0;
                }
                /*
                cout << " ====================== " << endl;
                cout << "edge : " << V1[X1] << endl;
                 */
                InDegreeV1 = graph.InOutDegree(V1[X1],V1);
                OutDegreeV1 = graph.InOutDegree(V1[X1],V2);
                /*
                cout << "edge : " << V2[X2] << endl;
                */
                OutDegreeV2 = graph.InOutDegree(V2[X2],V1);
                InDegreeV2 = graph.InOutDegree(V2[X2],V2);

                InDegrees = InDegreeV1 + InDegreeV2;
                OutDegrees = OutDegreeV1 + OutDegreeV2 - commun;

                if ( InDegrees < OutDegrees) {
                    /* cout << endl << endl;
                    //TEST
                    cout << "change : " << V1[X1] << " and " << V2[X2]<< endl;
                    // afficher V1 et V2
                    cout << "V1 : ";
                    for(int i=0; i<V1.size(); i++){
                        cout << V1[i] << " ";
                    }
                    cout << endl;
                    cout << "V2 : ";
                    for(int i=0; i<V2.size(); i++){
                        cout << V2[i] << " ";
                    }
                    cout << endl;

                    // afficher les  valeurs de la comparaison
                    cout << "V1: " << InDegreeV1 << " -- " << OutDegreeV1 << endl;
                    cout << "V2: " << InDegreeV2 << " -- " << OutDegreeV2 << endl;
                    cout << InDegrees << " -- " << OutDegrees << endl;
                    */
                    int temp = V1[X1];
                    V1[X1] = V2[X2];
                    V2[X2] = temp;
                    /*
                    // afficher V1 et V2
                    cout << "V1 : ";
                    for(int i=0; i<V1.size(); i++){
                        cout << V1[i] << " ";
                    }
                    cout << endl;
                    cout << "V2 : ";
                    for(int i=0; i<V2.size(); i++){
                        cout << V2[i] << " ";
                    }
                    cout << endl << endl;
                    */
                    change = true;
                }

            }
        //}
    }

    vector<vector<int>> result;
    result.push_back(V1);
    result.push_back(V2);

    return result;
}