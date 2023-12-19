/* ------------------------------------------------------------------------------ */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// INCLUDES \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ------------------------------------------------------------------------------ */

#include "model/GraphAdjacencyList.h"
#include "exact/ExactAlgorithm.h"
#include "constructive/ConstructiveHeuristic.h"
#include "local_search/LocalSearchHeuristic.h"

/* ----------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// DEFINES \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ----------------------------------------------------------------------------- */

/* --------- ALGORITHM CHOICE --------- */
//#define EXACT
//#define CONSTRUCTIVE
#define LOCAL
//#define TABU
/* --------- CREATE OUTPUT FILE ? --------- */
//#define OUTPUT
/* --------- PRINT TEST --------- */
#define TEST_LOCAL_CSV
//#define TEST_LOCAL_OUTPUT

int main(int argc, char *argv[]) {

/* ---------------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// GENERAL PARAMETERS \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------------- */

    int N = 10;                 // number of vertices
    int probEdges = 25;         // probability of having an edge between two vertices
    int maxIterations = 100;   // maximum number of iterations for every algorithm

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

/*
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
*/
    /*
    GraphAdjacencyList graph(6);
    graph.addEdge(0,3);
    graph.addEdge(0,2);
    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(2,5);
    graph.addEdge(4,2);*/

//    cout << "Nombre de sommet : " << graph.V << endl;
//    cout << "Nombre d'arretes maximum : " << numEdgesMax << endl;
//    cout << "Nombre d'arretes : " << numEdges << endl;
//    graph.printGraph();
//
//    vector<int> tabDegrees = graph.allDegrees();
//    cout << "Tableau degres : [";
//    for(const int &elem : tabDegrees){
//        cout << elem << " ";
//    }
//    cout << "]" << endl;

/* --------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Exact \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* --------------------------------------------------------------------------- */

#ifdef EXACT

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

#endif


/* -------------------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Constructive Heuristic \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* -------------------------------------------------------------------------------------------- */

#ifdef CONSTRUCTIVE
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

#endif

/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Local Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */

#ifdef LOCAL

    cout << "#---------------- LOCAL SEARCH ----------------#" << endl;

/* #==========# Initialize the parameters that will be used #==========# */

/* PARAMETERS FOR THE ALGORTIHM */
    // Initialize the graph
    GraphAdjacencyList graph_LocalSearch(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_Const;
    vector<vector<int>> subgraphs_LocalSearch;

/* PARAMETERS FOR THE FILE .out */
    int commonEdges_LocalSearch;
    int local_count;

/* PARAMETERS FOR THE CSV FILE */
    // Name of the csv file
    const string outputFileName = "../instances/local_search/execution_times_LocalSearch.csv";
    // Open the file to write in
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier CSV pour l'écriture." << endl;
        return 1;
    }
    // Write the header of the csv file
    outputFile << "Number of vertices, Execution time (seconds)" << endl;

/* PARAMETERS TO PRINT FOR THE TEST */
    int iteration = 1;

/* #==========# Execution of the local search algorithm #==========# */
    while (N <= maxIterations) {

        // Reset the graph and rebuild it with a new number of vertices N
        graph_LocalSearch.resetAndRebuild(N, probEdges);
#ifdef TEST_LOCAL_CSV
        cout << "ITERATION " << iteration << " - " << N << " points - ";
#endif
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graph_LocalSearch);
#ifdef TEST_LOCAL_CSV
        cout << "CONSTRUCTIVE - ";
#endif
        // start of the execution time
        auto start = chrono::high_resolution_clock::now();
        subgraphs_LocalSearch = LocalSearch(graph_LocalSearch, subgraphs_Const); // We put the result of the local search algorithm in a var
#ifdef TEST_LOCAL_CSV
        cout << "LOCAL - ";
#endif
        // end of the execution time
        auto end = chrono::high_resolution_clock::now();
        std::chrono::duration<double> temps_execution = end - start;
#ifdef TEST_LOCAL_CSV
        cout << "Time taken by function: " << temps_execution.count() << " seconds - " ;
#endif
        // write the number of vertices and the execution time in the csv file
        outputFile << N << ", " << temps_execution.count() << endl;
#ifdef TEST_LOCAL_CSV
        cout << "FIN" << endl;
#endif

/* Writing the result in the output file */
#ifdef OUTPUT
        // compute the number of common edges between the two subgraphs
        commonEdges_LocalSearch = calculEdgeCommun(graph_LocalSearch,subgraphs_LocalSearch);
        // Count the number of output files in the directory
        local_count = CountOutFilesInDirectory("../instances/local_search");

        // Directory to save the file
        std::string directory_local = "../instances/local_search/";
        // Write the result to the output file
        std::string filename_local = "test" + std::to_string(local_count) + "_local_search.out";
        WriteToFile(directory_local, filename_local, subgraphs_LocalSearch[0], subgraphs_LocalSearch[1], commonEdges_LocalSearch);
#endif

#ifdef TEST_LOCAL_OUTPUT
        // print the result expected in the output file
        // FIRST LINE : number of common edges between the two subgraphs
        cout << subgraphs_LocalSearch[0].size()+subgraphs_LocalSearch[1].size() << " " << commonEdges_LocalSearch << endl;
        // SECOND LINE : vertices of the first subgraph
        cout << "V1 : ";
        for(const int& element : subgraphs_LocalSearch[0]){
            cout << element << " ";
        }
        cout << endl;
        // THIRD LINE : vertices of the second subgraph
        cout << "V2 : ";
        for(const int& element : subgraphs_LocalSearch[1]){
            cout << element << " ";
        }
        cout << endl;
#endif

        N += 2;
        iteration++;
    }
#endif

/* --------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Tabu Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* --------------------------------------------------------------------------------- */
    cout << "#---------------- TABU SEARCH ----------------#" << endl;
/* Execution of the local search algorithm */





    return 0;
}