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
    cout << "Nombre d'arretes maximum : " << numEdgesMax << endl;
    cout << "Nombre d'arretes : " << numEdges << endl;
    graph.printGraph();

    vector<int> tabDegrees = graph.allDegrees();
    cout << "Tableau degres : [";
    for(const int &elem : tabDegrees){
        cout << elem << " ";
    }
    cout << "]" << endl;

/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Exact \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- EXACT ----------------#" << endl;
/* Execution of the exact algorithm */

    vector<int> vertices = {};
    for (int i = 0; i < graph.V; ++i) {
        vertices.push_back(i);
    }
    int min_cut = numeric_limits<int>::max();
    vector<int> best = {};
    ExactAlgorithm(graph, vertices, min_cut, best);

    // FIRST LINE : the number vertices of the graph followed by the number of edges of the solution
    cout << vertices.size() << " " << min_cut << endl;
    // SECOND LINE : vertices of the first subgraph
    vector<int> subgraph2 = deduire_subgraph2(vertices, best);
    cout << "V1 : ";
    affiche_vector(best);
    cout << endl;
    //THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    affiche_vector(subgraph2);
    cout << endl;

    /* Writing the result in the output file */
    // Count the number of output files in the directory
    int exact_count = CountOutFilesInDirectory("../instances/exact");

    // Directory to save the file
    std::string directory_exact = "../instances/exact/";

    // Write the result to the output file
    std::string filename_exact = "test" + std::to_string(exact_count) + "_exact.out";
    WriteToFile(directory_exact, filename_exact, best, subgraph2, min_cut);


/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Constructive Heuristic \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- CONSTRUCTIVE HEURISTIC ----------------#" << endl;
/* Execution of the constructive heuristic algorithm */

    // Apply the constructive heuristic to the graph
    vector<vector<int>> constructiveHeuristic_subgraphs = ConstructiveHeuristic(graph);

    // compute the number of common edges between the two subgraphs
    int commonEdges_ConstructiveHeuristic = calculEdgeCommun(graph,constructiveHeuristic_subgraphs);

    // print the result expected in the output file
    // FIRST LINE : the number vertices of the graph followed by the number of edges of the solution
    cout << constructiveHeuristic_subgraphs[0].size()+constructiveHeuristic_subgraphs[1].size() << " " << commonEdges_ConstructiveHeuristic << endl;

    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : constructiveHeuristic_subgraphs[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : constructiveHeuristic_subgraphs[1]){
        cout << element << " ";
    }
    cout << endl;

/* Writing the result in the output file */
    // Count the number of output files in the directory
    int constructive_heuristic_count = CountOutFilesInDirectory("../instances/constructive");

    // Directory to save the file
    std::string directory_constructive = "../instances/constructive/";

    // Write the result to the output file
    std::string filename_constructive = "test" + std::to_string(constructive_heuristic_count) + "_constructive.out";
    WriteToFile(directory_constructive, filename_constructive, constructiveHeuristic_subgraphs[0], constructiveHeuristic_subgraphs[1], commonEdges_ConstructiveHeuristic);


/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Local Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- LOCAL SEARCH ----------------#" << endl;
/* Execution of the local search algorithm */
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
    // Count the number of output files in the directory
    int local_search_count = CountOutFilesInDirectory("../instances/local_search");

    // Directory to save the file
    std::string directory_localSearch = "../instances/local_search/";

    // Write the result to the output file
    std::string filename_localSearch = "test" + std::to_string(local_search_count) + "_local_search.out";
    WriteToFile(directory_localSearch, filename_localSearch, localSearch_subgraphs[0], localSearch_subgraphs[1], commonEdges_LocalSearch);


/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Tabu Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- TABU SEARCH ----------------#" << endl;
/* Execution of the local search algorithm */



/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Execution time \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */
    cout << "#---------------- EXECUTION TIME ----------------#" << endl;
/* Write time complexity in the csv file */
    //Create csv files
    const string outputFileNameExact = "../instances/exact/execution_times_Exact.csv";
    const string outputFileNameConstructive = "../instances/constructive/execution_times_Constructive.csv";
    const string outputFileNameLocal = "../instances/local_search/execution_times_LocalSearch.csv";
    //const string outputFileNameTabu = "../instances/tabu_search/execution_times_Tabu.csv";

    // Open all files to write in
    ofstream outputFileExact(outputFileNameExact);
    if (!outputFileExact.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier Exact CSV pour l'écriture." << endl;
        return 1;
    }
    ofstream outputFileLocal(outputFileNameLocal);
    if (!outputFileLocal.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier Local Search CSV pour l'écriture." << endl;
        return 1;
    }
    ofstream outputFileConstructive(outputFileNameConstructive);
    if (!outputFileConstructive.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier Constructive CSV pour l'écriture." << endl;
        return 1;
    }

    // Write the header of the csv file
    outputFileExact << "Nombre de points, Temps d'exécution (s)" << endl;
    outputFileLocal << "Nombre de points, Temps d'exécution (s)" << endl;
    outputFileConstructive << "Nombre de points, Temps d'exécution (s)" << endl;

    //Creat the graph for all tests
    GraphAdjacencyList graphTimeExe(0);
    int probEdges_LocalSearch = 25;
    vector<vector<int>> subgraphs_Exact;
    vector<vector<int>> subgraphs_Const;
    vector<vector<int>> subgraphs_Constructive;
    vector<vector<int>> subgraphs_LocalSearch;

    int iteration = 1;
    cout << "------------------------------------------------" << endl;
    for (int N = 10; N <= 200; N +=10) {
        // Génère le graphe de N points
        graphTimeExe.resetAndRebuild(N, probEdges_LocalSearch);

        /*----------EXACT----------*/
        /*
        //Start the chrono
        auto startExact = chrono::high_resolution_clock::now();
        //Execute the function
        vector<int> tabVertices = {};
        for (int i = 0; i < graphTimeExe.V; ++i) {
            tabVertices.push_back(i);
        }
        int min_cut_exact = numeric_limits<int>::max();
        vector<int> best = {};
        subgraphs_Exact =

        //Stop the chrono
        auto endExact = chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_execution_Exact = endExact - startExact;

        cout << endl << "ITERATION " << iteration << " - " << N << " points - CONSTRUCTIVE - ";
        cout << "Time taken by function: " << temps_execution_Exact.count() << " seconds " ;
        // Write the informations in the CSV file
        outputFileExact << N << ", " << temps_execution_Exact.count() << endl;
        */
        /*----------CONSTRUCTIVE----------*/
        //Start the chrono
        auto startConstructive = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_Constructive = ConstructiveHeuristic(graphTimeExe);
        //Stop the chrono
        auto endConstructive = chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_execution_Constructive = endConstructive - startConstructive;

        cout << endl << "ITERATION " << iteration << " - " << N << " points - CONSTRUCTIVE - ";
        cout << "Time taken by function: " << temps_execution_Constructive.count() << " seconds " ;
        // Write the informations in the CSV file
        outputFileConstructive << N << ", " << temps_execution_Constructive.count() << endl;

        /*----------LOCAL-SEARCH----------*/
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graphTimeExe);
        //Start the chrono
        auto startLocal = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_LocalSearch = LocalSearch(graphTimeExe, subgraphs_Const);
        //Stop the chrono
        auto endLocal = chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_execution_Local = endLocal - startLocal;

        cout << endl << "ITERATION " << iteration << " - " << N << " points - LOCAL - ";
        cout << "Time taken by function: " << temps_execution_Local.count() << " seconds " ;
        // Write the informations in the CSV file
        outputFileLocal << N << ", " << temps_execution_Local.count() << endl;

        iteration++;
    }


/*
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
    for (int N = 16; N <= 20; N += 2) {
        cout << endl << "ITERATION " << iteration << " - " << N << " points - ";
        iteration++;
        // Génère le graphe de N points
        graph_LocalSearch.resetAndRebuild(N, probEdges_LocalSearch);
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graph_LocalSearch);
        cout << "CONSTRUCTIVE - ";

        //Start the chrono
        auto start = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_LocalSearch = LocalSearch(graph_LocalSearch, subgraphs_Const);
        cout << "LOCAL - ";
        //Stop the chrono
        auto end = chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_execution = end - start;

        cout << "Time taken by function: " << temps_execution.count() << " microseconds - " ;

        // Écrit les informations dans le fichier CSV
        outputFile << N << ", " << temps_execution.count() << endl;

        cout << "FIN" << endl;
    }

*/
    return 0;
}
