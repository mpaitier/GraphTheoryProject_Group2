#include <cstdlib>
#include <iostream>
#include <vector>

#include "model/GraphAdjacencyList.h"
#include "exact/ExactAlgorithm.h"
#include "constructive/ConstructiveHeuristic.h"
#include "local_search/LocalSearchHeuristic.h"

int main(int argc, char *argv[]) {

    //Crée un graph de manière aléatoire avec maximum 20 sommets
    srand(time(NULL));
    int numVertices = rand()%20+1;
    if(numVertices%2 !=0){      //verifier nombre de sommets paire
        numVertices = numVertices + 1;
    }
    GraphAdjacencyList graph(numVertices);
    int edges = (numVertices*(numVertices-1))/2;
    int numEdgesMax = (rand() % (edges - (edges/2) + 1)) + (edges/2);
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

    /*
    GraphAdjacencyList graph(6);
    graph.addEdge(0,3);
    graph.addEdge(0,2);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(2,5);
    graph.addEdge(4,2);*/

    cout << "Nombre de sommet : " << graph.V << endl;
    /*
    cout << "Nombre d'arretes maximum : " << numEdgesMax << endl;
    cout << "Nombre d'arretes : " << numEdges << endl; */
    graph.printGraph();

    vector<int> tabDegrees = graph.allDegrees();
    cout << "Tableau degres : [";
    for(const int &elem : tabDegrees){
        cout << elem << " ";
    }
    cout << "]" << endl;
    /*
    cout << "CONSTRUCTIVE HEURISTIC" << endl;
    vector<vector<int>> subgraphs = ConstructiveHeuristic(graph);

    int edgesCommuns = calculEdgeCommun(graph,subgraphs);
    cout << "nbr arretes communes entre les deux sous graphes : " << edgesCommuns << endl;
    */

/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Local Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- LOCAL SEARCH ----------------#" << endl;
/* Execution of the local search algortihm */
    // Apply the local search heuristic to the graph
    vector<vector<int>> localSearch_subgraphs = LocalSearch(graph);

    // compute the number of common edges between the two subgraphs
    int commonEdges_LocalSearch = calculEdgeCommun(graph,localSearch_subgraphs);

    // print the result expected in the output file
    // FIRST LINE : number of common edges between the two subgraphs
    cout << localSearch_subgraphs[0].size()+localSearch_subgraphs[1].size() << " " << commonEdges_LocalSearch << endl;
    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : localSearch_subgraphs[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : localSearch_subgraphs[1]){
        cout << element << " ";
    }
    cout << endl;

/* Writting the result in the output file */
    // Count the number of output files in the directory
    int local_search_count = CountOutFilesInDirectory("../instances/local_search");

    // Directory to save the file
    std::string directory = "../instances/local_search/";

    // Write the result to the output file
    std::string filename = "test" + std::to_string(local_search_count) + "_local_search.out";
    WriteToFile(directory, filename, localSearch_subgraphs[0], localSearch_subgraphs[1], commonEdges_LocalSearch);

/*
//Test function ConstructiveHeuristic and calculEdgeCommun
    int numVertices = 6;
    GraphAdjacencyList G(numVertices);
    G.addEdge(1,2);
    G.addEdge(1,3);
    G.addEdge(1,4);
    G.addEdge(2,3);
    G.addEdge(2,4);
    G.addEdge(2,5);
    G.addEdge(3,5);
    G.addEdge(3,0);
    G.addEdge(4,5);
    G.addEdge(5,0);
    G.printGraph();

    vector<int> tabDegrees = G.allDegrees();
    cout << "Tableau degres : [";
    for(const int &elem : tabDegrees){
        cout << elem << " ";
    }
    cout << "]" << endl;

    cout << "CONSTRUCTIVE HEURISTIC" << endl;
    vector<vector<int>> subgraphs = ConstructiveHeuristic(G);

    int edgesCommuns = calculEdgeCommun(G,subgraphs);
    cout << "nbr arretes communes entre les deux sous graphes : " << edgesCommuns << endl;
*/

/*
    // ALGORITHME EXACT test avec le graphe G
    cout << "\nALGO EXACT" << endl;
    vector<int> vertices = {};
    for (int i = 0; i < G.V; ++i) {
        vertices.push_back(i);
    }
    int min_cut = numeric_limits<int>::max();
    vector<int> best = {};
    powerSet(G, vertices, min_cut, best);
    cout << "==> Min cut : " << min_cut << endl;
    cout << "==> Best partition : ";
    affiche_vector(best);
    cout << " - ";
    affiche_vector(deduire_subgraph2(vertices, best));
*/
    
/*
//Test function calculEdgeCommun
    vector<vector<int>> subgraphs ;
    vector<int> V1 = {1,4,5};
    subgraphs.push_back(V1);
    vector<int> V2 = {2,3,0};
    subgraphs.push_back(V2);

    for(const auto& sousgraph : subgraphs){
        cout << "sous graph : ";
        for(const int& element : sousgraph){
            cout << element << " ";
        }
        cout << endl;
    }

    int som = calculEdgeCommun(G,subgraphs);
    cout << "nbr arretes communes entre les deux sous graphes : " << som <<  " (6)" <<endl;
*/


    return 0;
}
