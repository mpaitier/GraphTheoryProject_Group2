#include <cstdlib>
#include <iostream>
#include <vector>

#include "model/GraphAdjacencyList.h"
#include "exact/ExactAlgorithm.h"
#include "constructive/ConstructiveHeuristic.h"
#include "local_search/LocalSearchHeuristic.h"

int main(int argc, char *argv[]) {

/*
    // ----------------------------------------------------------------
    // Récupérer les données du fichier input
    // ----------------------------------------------------------------
    // int nbVertices : nombre de sommets
    // int nbEdges : nombre d'arêtes
    // vector<int> edges : vecteur d'entiers correspondant aux arêtes
    // ----------------------------------------------------------------
    
    ifstream input_file("../filename.in");

    if(input_file)
    {
        string ligne;
        input_file.seekg(0, ios::beg);

        int nbVertices;
        int nbEdges;

        input_file >> nbVertices;
        input_file >> nbEdges;

        vector<int> edges;

        for (int i = 0; i < nbEdges; ++i) {
            int u, v, weight;
            input_file >> u >> v >> weight;

            edges.push_back(u);
            edges.push_back(v);
            edges.push_back(weight);
        }


    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }


    input_file.close();
*/

    
    //Crée un graph de manière aléatoire avec maximum 20 sommets
    srand(time(NULL));
    /*
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
     */


    GraphAdjacencyList graph(6);
    graph.addEdge(0,3);
    graph.addEdge(0,2);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(2,5);
    graph.addEdge(4,2);


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
/* <-------------# Test resetAndRebuild #------------->*/
//    graph.resetAndRebuild(10,25);
//
//    cout << "Nombre de sommet : " << graph.V << endl;
//
//    graph.printGraph();
//
//    tabDegrees = graph.allDegrees();
//    cout << "Tableau degres : [";
//    for(const int &elem : tabDegrees){
//        cout << elem << " ";
//    }
//    cout << "]" << endl;

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
    vector<vector<int>> SG = ConstructiveHeuristic(graph);
    vector<vector<int>> localSearch_subgraphs = LocalSearch(graph,SG);

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
/*
    // Count the number of output files in the directory
    int local_search_count = CountOutFilesInDirectory("../instances/local_search");

    // Directory to save the file
    std::string directory = "../instances/local_search/";

    // Write the result to the output file
    std::string filename = "test" + std::to_string(local_search_count) + "_local_search.out";
    WriteToFile(directory, filename, localSearch_subgraphs[0], localSearch_subgraphs[1], commonEdges_LocalSearch);
*/

/* Writte time complexity in the csv file */

/* CE QUI NE FONCTIONNE PAS */
    const string outputFileName = "../instances/local_search/execution_times_LocalSearch.csv";

    // Open the file to write in
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier CSV pour l'écriture." << endl;
        return 1;
    }

    // Write the header of the csv file
    outputFile << "Nombre de points, Temps d'exécution (ms)" << endl;

    GraphAdjacencyList graph_LocalSearch(0);
    int probEdges_LocalSearch = 25;
    vector<vector<int>> subgraphs_Const;
    vector<vector<int>> subgraphs_LocalSearch;

    int iteration = 1;
    cout << "------------------------------------------------" << endl;
    for (int N = 10; N <= 20; N += 2) {
        cout << endl << "ITERATION " << iteration << " - " << N << " points - ";
        iteration++;
        // Génère le graphe de N points
        graph_LocalSearch.resetAndRebuild(N, probEdges_LocalSearch);
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graph_LocalSearch);
        cout << "CONSTRUCTIVE - ";

        auto start = chrono::high_resolution_clock::now();

        subgraphs_LocalSearch = LocalSearch(graph_LocalSearch, subgraphs_Const);
        cout << "LOCAL - ";

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "Time taken by function: "
             << duration << " microseconds - " ;

        // Écrit les informations dans le fichier CSV
        outputFile << N << "," << duration << endl;
        cout << "FIN" << endl;
    }
    cout << "HELLO" << endl;

/* FIN DE CE QUI NE FONCIONNE PAS */

/* J'ai un autre fichier où j'arrive à obtenir des valeurs pour le temps d'execution mais je n'arrive pas à les écrire dans le fichier CSV
#include <iostream>

#include <algorithm>
#include <chrono>
#include<vector>
using namespace std;
using namespace std::chrono;

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include <cstdlib>
#include <string>


#include "model/GraphAdjacencyList.h"
#include "exact/ExactAlgorithm.h"
#include "constructive/ConstructiveHeuristic.h"
#include "local_search/LocalSearchHeuristic.h"


int main()
{

    srand(time(NULL));

    const string outputFileName = "execution_times_LocalSearch.csv";

    // Open the file to write in
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier CSV pour l'écriture." << endl;
        return 1;
    }

    // Write the header of the csv file
    outputFile << "Nombre de points, Temps d'exécution (ms)" << endl;

    GraphAdjacencyList graph_LocalSearch(0);
    int probEdges_LocalSearch = 25;
    vector<vector<int>> subgraphs_Const;
    vector<vector<int>> subgraphs_LocalSearch;

    int iteration = 1;
    for(int N = 10; N < 20; N+=2) {
        cout << endl << "ITERATION " << iteration << " - " << N << " points - ";
        iteration++;
        // Génère le graphe de N points avec une probabilité d'arête de 25%
        graph_LocalSearch.resetAndRebuild(N, probEdges_LocalSearch);
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graph_LocalSearch);

        cout << "CONSTRUCTIVE - ";
        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // Call the function, here sort()
        subgraphs_LocalSearch = LocalSearch(graph_LocalSearch, subgraphs_Const);
        cout << "LOCAL - ";

        // Get ending timepoint
        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;

        cout << "FIN" << endl;
    }


    return 0;
}
*/

/* ---------------------------------------------------------------------------------- */


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
