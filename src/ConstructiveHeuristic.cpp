#include "ConstructiveHeuristic.h"
#include "GraphAdjacencyList.h"

vector<vector<int>> ConstructiveHeuristic(GraphAdjacencyList G){
    vector<int> tabDegrees = G.allDegrees();
    int n = (G.V)/2;    //nombre de sommets max pr V1 et V2
    vector<int> allVertex;      //vector avec tout les vertex encore à placer
    for(int i=0; i<G.V; i++){
        allVertex.push_back(i);
    }
    vector<int> V1;
    vector<int> V2;
    vector<vector<int>> vectors;

    //Ajout ds V1 sommet plus haut degré
    //int vertexHighDegree = max_element(tabDegrees.begin(), tabDegrees.end());
    int vertexHighDegree = 0;
    for(int i=1; i<tabDegrees.size(); i++){
        if(tabDegrees[vertexHighDegree] < tabDegrees[i]){
            vertexHighDegree = i;       //prend le premier sommet le plus haut si egalite
        }
    }
    V1.push_back(vertexHighDegree);

    //Rempli V1
    int vertex = vertexHighDegree;
    auto posVertex = find(allVertex.begin(), allVertex.end(), vertex);
    allVertex.erase(posVertex);

    while(V1.size() <= n){

        //recherche tout les voisins de vertex encore ds allVertex
        vector<int> tabNeighbor;
        for(const int& neighbor : G.adjacencyList[vertex]){
            auto isInAllVertex = find(allVertex.begin(), allVertex.end(), neighbor);
            if(isInAllVertex != allVertex.end()){
                tabNeighbor.push_back(neighbor);
            }
        }

        if(!tabNeighbor.empty()){       //regarde si vertex a encore des voisins ds allVertex
            int v = G.adjacencyList[vertex][0];
            for(const int& neighbor : G.adjacencyList[vertex]){
                //recherche la position du voisin ds allVertex
                auto isInAllVertex = find(allVertex.begin(), allVertex.end(), neighbor);
                //recupere sommet + haut degre ds les voisins et verifie si present ds allVertex
                if(tabDegrees[v] < tabDegrees[neighbor] && isInAllVertex != allVertex.end()){
                    v = neighbor;
                }
            }
            auto var = find(V1.begin(), V1.end(), v);    //recherche la position de la valeur, si la valeur n'est pas presente var=V1.end;
            if(var == V1.end()){
                V1.push_back(v);        //ajoute le sommet ds V1
                auto pos = find(allVertex.begin(), allVertex.end(), v);     //recherche la position de v ds allVertex
                allVertex.erase(pos);       //supprime le sommet ds allVertex
            }
        }
        else{       //regarde les autres sommets ds V1 pour trouver des voisins de + haut degre
            int v;
            for(const int &elem : V1){
                v = G.adjacencyList[elem][0];
                for(const int& neighbor : G.adjacencyList[elem]){
                    //recherche la position du voisin ds allVertex
                    auto isInAllVertex = find(allVertex.begin(), allVertex.end(), neighbor);
                    //recupere sommet + haut degre ds les voisins et verifie si present ds allVertex
                    if(tabDegrees[v] < tabDegrees[neighbor] && isInAllVertex != allVertex.end()){
                        v = neighbor;
                    }
                }
            }
            auto var = find(V1.begin(), V1.end(), v);    //recherche la position de la valeur, si la valeur n'est pas presente var=V1.end;
            if(var == V1.end()){
                V1.push_back(v);        //ajoute le sommet ds V1
                auto pos = find(allVertex.begin(), allVertex.end(), v);     //recherche la position de v ds allVertex
                allVertex.erase(pos);       //supprime le sommet ds allVertex
            }
        }
    }

    //Rempli V2 avec les sommets qui ne sont pas dans V1
    for(int i=0; i<G.V; i++){
        auto var = find(V1.begin(), V1.end(), i);    //recherche la position de la valeur, si la valeur n'est pas presente var=V1.end;
        if(var == V1.end()){
            V2.push_back(i);
        }
    }

    vectors.push_back(V1);
    vectors.push_back(V2);
    return vectors;
}
