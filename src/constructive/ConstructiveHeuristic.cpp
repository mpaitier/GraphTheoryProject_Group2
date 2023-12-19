#include "ConstructiveHeuristic.h"
#include "../model/GraphAdjacencyList.h"

vector<vector<int>> ConstructiveHeuristic(GraphAdjacencyList G){
    vector<int> tabDegrees = G.allDegrees();
    int n = (G.V)/2;    //nombre de sommets max pr V1 et V2
    vector<int> allVertex;      //vector avec tout les vertex encore à placer
    for(int i=0; i<G.V; i++){
        allVertex.push_back(i);
    }

    //TEST : verifie all vertex
//    cout << "allvertex : " ;
//    for(int i=0; i<allVertex.size(); i++){
//        cout << allVertex[i] << " ";
//    }
//    cout << endl;

    vector<int> V1;
    vector<int> V2;
    vector<vector<int>> vectors;

    //Ajout ds V1 sommet plus haut degré
    int vertexHighDegree = 0;
    for(int i=1; i<tabDegrees.size(); i++){
        if(tabDegrees[vertexHighDegree] < tabDegrees[i]){
            vertexHighDegree = i;       //prend le premier sommet le plus haut si egalite
        }
    }
    //TEST : high vertex
    //cout << "high vertex : " << vertexHighDegree << endl;
    V1.push_back(vertexHighDegree);

    int vertex = vertexHighDegree;
    auto posVertex = find(allVertex.begin(), allVertex.end(), vertex);
    allVertex.erase(posVertex);

    //TEST : verifie si high vertex a ete enlever de allvertex
//    cout << "allvertex : " ;
//    for(int i=0; i<allVertex.size(); i++){
//        cout << allVertex[i] << " ";
//    }
//    cout << endl;

    //Rempli V1
    while(V1.size() < n){
        //cout << "vertex : " << vertex << endl;
        //recherche tout les voisins de vertex encore ds allVertex
        vector<int> tabNeighbor;
        for(const int& neighbor : G.adjacencyList[vertex]){
            bool isInAllVertex = valPresent(allVertex, neighbor);
            if(isInAllVertex == true){
                tabNeighbor.push_back(neighbor);
            }
        }

        //verifie si vertex a encore des voisins ds allVertex
        if(!tabNeighbor.empty()){
            //TEST
//            cout << "tabNeighbor : ";
//            for(int i=0; i<tabNeighbor.size(); i++){
//                cout << tabNeighbor[i] << " ";
//            }
//            cout << endl;

            int &v = tabNeighbor[0];
            for(const int& neighbor : G.adjacencyList[vertex]){
                //verifie si le voisin est ds allvertex
                bool isInAllVertex = valPresent(allVertex, neighbor);
                //TEST
//                cout << neighbor << " est ds all vertex : " << isInAllVertex << endl;
//                //recupere sommet + haut degre ds les voisins et verifie si present ds allVertex
//                cout << "degree v : " << tabDegrees[v] << endl;
//                cout << "degree neighbor : " << tabDegrees[neighbor] << endl;
                if(tabDegrees[v] < tabDegrees[neighbor] && isInAllVertex == 1){
                    v = neighbor;
                }
            }
            //TEST
            //cout << "v choisit : " << v << endl;
            //verifie si la valeur est pas deja présente ds V1
            bool var = valPresent(V1, v);
            //TEST
            //cout << "v est deja present ds V1 : " << var << endl;
            if(var == 0){
                //cout << "ok v pas present ds V1" << endl;
                V1.push_back(v);        //ajoute le sommet ds V1
                auto posAllVertex = find(allVertex.begin(), allVertex.end(), v);     //recherche la position de v ds allVertex
                allVertex.erase(posAllVertex);       //supprime le sommet ds allVertex
                auto posTabNeighbor = find(tabNeighbor.begin(), tabNeighbor.end(),v);
                tabNeighbor.erase(posTabNeighbor);
            }

        }

        //regarde les autres sommets ds V1 pour trouver des voisins de + haut degre
        //if(tabNeighbor.empty()){
        else{
            //cout << "rentre"<< endl;
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
                    //verifie que le voisin est ds allvertex
                    bool isInAllVertex = valPresent(allVertex, neighbor);
                    //recupère sommet + haut degre ds les voisins et verifie si present ds allVertex
                    if(tabDegrees[vertex] < tabDegrees[neighbor] && isInAllVertex == true){
                        vertex = neighbor;
                    }
                }
                /*for(const int& neighbor : G.adjacencyList[elem]){
                    //verifie que le voisin est ds allvertex
                    bool isInAllVertex = valPresent(allVertex, neighbor);
                    //recupère sommet + haut degre ds les voisins et verifie si present ds allVertex
                    if(tabDegrees[v] < tabDegrees[neighbor] && isInAllVertex == true){
                        v = neighbor;
                    }
                }*/
            }
            //verifie si la valeur est pas deja présente ds V1
            bool var = valPresent(V1, vertex);
            if(var == false){
                V1.push_back(vertex);        //ajoute le sommet ds V1
                auto posAllVertex = find(allVertex.begin(), allVertex.end(), vertex);     //recherche la position de v ds allVertex
                allVertex.erase(posAllVertex);       //supprime le sommet ds allVertex
            }
        }
    }

    //Rempli V2 avec les sommets qui ne sont pas dans V1
    for(int i=0; i<G.V; i++){
        bool var = valPresent(V1, i);       //verifie si la valeur est deja ds V1
        if(var == false){
            V2.push_back(i);
        }
    }

    vectors.push_back(V1);
    //TEST
//    cout << "V1 : ";
//    for(int i=0; i<vectors[0].size(); i++){
//        cout << vectors[0][i] << " ";
//    }
//    cout << endl;
    vectors.push_back(V2);
//    //TEST
//    cout << "V2 : ";
//    for(int i=0; i<vectors[1].size(); i++){
//        cout << vectors[1][i] << " ";
//    }
//    cout << endl;
    return vectors;
}


bool valPresent(vector<int> vector, int val){
    unordered_set<int> ensemble(vector.begin(), vector.end());
    return ensemble.count(val) > 0;
}