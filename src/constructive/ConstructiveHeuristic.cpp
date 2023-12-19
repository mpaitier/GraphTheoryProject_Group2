#include "ConstructiveHeuristic.h"
#include "../model/GraphAdjacencyList.h"

vector<vector<int>> ConstructiveHeuristic(GraphAdjacencyList G){
    vector<int> tabDegrees = G.allDegrees();
    int n = (G.V)/2;    //number maximum of vertices for V1 and V2
    vector<int> allVertex;      //vector with all vertices to place
    for(int i=0; i<G.V; i++){
        allVertex.push_back(i);
    }
    vector<int> V1;
    vector<int> V2;
    vector<vector<int>> vectors;

    //Put in V1 the vertex with the highest degree
    int vertexHighDegree = 0;
    for(int i=1; i<tabDegrees.size(); i++){
        if(tabDegrees[vertexHighDegree] < tabDegrees[i]){
            vertexHighDegree = i;       //take the first vertex with highest deggree if there is equality
        }
    }
    V1.push_back(vertexHighDegree);

    int vertex = vertexHighDegree;
    auto posVertex = find(allVertex.begin(), allVertex.end(), vertex);
    allVertex.erase(posVertex);

    //Fill V1
    while(V1.size() < n){
        //search all vertex neighbors still in allVertex
        vector<int> tabNeighbor;
        for(const int& neighbor : G.adjacencyList[vertex]){
            bool isInAllVertex = valPresent(allVertex, neighbor);
            if(isInAllVertex == true){
                tabNeighbor.push_back(neighbor);
            }
        }

        //checks if vertex still has neighbors ds allVertex
        if(!tabNeighbor.empty()){
            int &v = tabNeighbor[0];
            for(const int& neighbor : G.adjacencyList[vertex]){
                //checks if the neighbor is ds allvertex
                bool isInAllVertex = valPresent(allVertex, neighbor);
                //get the top from the highest degree of the neighbors and check if present ds allVertex
                if(tabDegrees[v] < tabDegrees[neighbor] && isInAllVertex == 1){
                    v = neighbor;
                }
            }
            //check if vertex is not in V1
            bool var = valPresent(V1, v);
            if(var == 0){
                V1.push_back(v);        //put the vertex in V1
                auto posAllVertex = find(allVertex.begin(), allVertex.end(), v);     //searches for the position of v in allVertex
                allVertex.erase(posAllVertex);       //erase the vertex of allVertex
                auto posTabNeighbor = find(tabNeighbor.begin(), tabNeighbor.end(),v);   //searches for the position of v in tabNeighbors
                tabNeighbor.erase(posTabNeighbor);      //erase the vertex of tabNeighbors
            }

        }

            //look at the other vertices in V1 to find neighbors of higher degree
        else{
            int v;
            for(const int &elem : V1){
                int v = V1[1];
                for(int i=0; i<V1.size(); i++){
                    if(tabDegrees[v] < tabDegrees[V1[i]] && V1[i] != vertexHighDegree){
                        v = V1[i];
                    }
                }
                for(const int& neighbor : G.adjacencyList[v]){
                    vertex = G.adjacencyList[v][0];
                    //checks if the neighbor is ds allvertex
                    bool isInAllVertex = valPresent(allVertex, neighbor);
                    //get the top from the highest degree of the neighbors and check if present ds allVertex
                    if(tabDegrees[vertex] < tabDegrees[neighbor] && isInAllVertex == true){
                        vertex = neighbor;
                    }
                }
            }
            //check if vertex is not in V1
            bool var = valPresent(V1, vertex);
            if(var == false){
                V1.push_back(vertex);        //put the vertex in V1
                auto posAllVertex = find(allVertex.begin(), allVertex.end(), vertex);     //searches for the position of v in allVertex
                allVertex.erase(posAllVertex);       //erase the vertex of allVertex
            }
        }
    }

    //Fill V2 with all vertices not present in V1
    for(int i=0; i<G.V; i++){
        bool var = valPresent(V1, i);       //vcheck if vertex is in V1
        if(var == false){
            V2.push_back(i);
        }
    }

    //Fill vectors with both subgraphs
    vectors.push_back(V1);
    vectors.push_back(V2);
    return vectors;
}


bool valPresent(vector<int> vector, int val){
    unordered_set<int> ensemble(vector.begin(), vector.end());
    return ensemble.count(val) > 0;
}