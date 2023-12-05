#include <cstdlib>
#include <iostream>

#include "GraphAdjacencylist.h"
#include "ConstructiveHeuristic.h"

int main(int argc, char *argv[]) {

    //Crée un graph de manière aléatoire avec maximum 20 sommets
    srand(time(NULL));
    int numVertices = rand()%20+1;
    if(numVertices%2 !=0){      //verifier nombre de sommets paire
        numVertices = numVertices + 1;
    }
    GraphAdjacencyList graph(numVertices);
    int numEdgesMax = rand() % ((numVertices*(numVertices-1))/2);
    int numEdges = 0;
    for(int i=0; i<numEdgesMax; i++){
        int randomVertex1 = rand() %numVertices;
        int randomVertex2 = rand() %numVertices;
        if(randomVertex1 != randomVertex2){
            if(graph.adjacencyList[randomVertex1].empty()){
                graph.addEdge(randomVertex1, randomVertex2);
                numEdges ++;
            }
            else{
                bool valid = true;
                for(const int &neighbor : graph.adjacencyList[randomVertex1]){
                    if(neighbor == randomVertex2){
                        valid = false;
                    }
                }
                if(valid){
                    graph.addEdge(randomVertex1, randomVertex2);
                    numEdges ++;
                }
            }
        }
    }

    cout << "Nombre de sommet : " << graph.V << endl;
    cout << "Nombre d'arretes maximum : " << numEdgesMax << endl;
    cout << "Nombre d'arretes : " << numEdges << endl;
    graph.printGraph();

    vector<int> tabDegrees = graph.allDegrees();
    cout << "Tableau degres : [";
    for(const int &elem : tabDegrees){
        cout << elem << " ";
    }
    cout << "]" << endl;

    return 0;
}