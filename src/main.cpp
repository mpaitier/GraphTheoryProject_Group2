/* ------------------------------------------------------------------------------ */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// INCLUDES \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ------------------------------------------------------------------------------ */

#include "model/GraphAdjacencyList.h"
#include "exact/ExactAlgorithm.h"
#include "constructive/ConstructiveHeuristic.h"
#include "tabu_search/TabuSearch.h"

/* ----------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// DEFINES \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ----------------------------------------------------------------------------- */

/* --------- ALGORITHM CHOICE --------- */
//#define EXACT
//#define CONSTRUCTIVE
//#define LOCAL
//#define TABU
//#define ALL
/* --------- CREATE OUTPUT FILE FROM ALGORITHM --------- */
//#define OUTPUT
/* --------- CREATE OUTPUT FILE FROM INPUT FILE ? --------- */
//#define EXACT_WITH_IN_FILES
//#define CONSTRUCTIVE_WITH_IN_FILES
//#define LOCAL_WITH_IN_FILES
//#define TABU_WITH_IN_FILES



int main(int argc, char *argv[]) {

/* ---------------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// GENERAL PARAMETERS \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------------- */

    srand(time(NULL));

    int step = 2;
    int N;
    int N_base = 4;            // number of vertices at the beginning
    int probEdges = 75;         // probability of having an edge between two vertices
    int maxIterations = 20;    // maximum number of iterations for every algorithm


/* --------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Exact \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* --------------------------------------------------------------------------- */

#ifdef EXACT

    cout << "#---------------- EXACT ----------------#" << endl;

/* #==========# Initialize the parameters that will be used #==========# */

/* PARAMETERS FOR THE ALGORTIHM */
    // Number of vertices
    N = N_base;
    // Initialize the graph
    GraphAdjacencyList graph_Exact(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_Exact;

/* PARAMETERS FOR THE FILE .out */
    int commonEdges_Exact;
    int exact_count;

/* PARAMETERS FOR THE CSV FILE */
    // Name of the csv file
    const string outputFileNameExact = "../instances/exact/execution_times_Exact.csv";
    // Open the file to write in
    ofstream outputFileExact(outputFileNameExact);
    if (!outputFileExact.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }

/* PARAMETERS TO PRINT FOR THE TEST */
    int iteration_exact = 1;

/* #==========# Execution of the local search algorithm #==========# */
    while (N <= maxIterations) {

        // Reset the graph and rebuild it with a new number of vertices N
        graph_Exact.resetAndRebuild(N, probEdges);
        cout << "ITERATION " << iteration_exact << " - " << N << " points - ";

        // start of the execution time
        auto startExact = chrono::high_resolution_clock::now();
        subgraphs_Exact = Exact_Main(graph_Exact);

        // end of the execution time
        auto endExact = chrono::high_resolution_clock::now();
        int temps_execution_exact = std::chrono::duration_cast<chrono::microseconds>(endExact - startExact).count();

        cout << "Time taken by function: " << temps_execution_exact << " microseconds - " ;

        // write the number of vertices and the execution time in the csv file
        outputFileExact << N << ", " << temps_execution_exact << endl;

        cout << "FIN" << endl;

/* Writing the result in the output file */
#ifdef OUTPUT
        // compute the number of common edges between the two subgraphs
        commonEdges_Exact = calculEdgeCommun(graph_Exact, subgraphs_Exact);
        // Count the number of output files in the directory
        exact_count = CountOutFilesInDirectory("../instances/exact");

        // Directory to save the file
        std::string directory_exact = "../instances/exact/";
        // Write the result to the output file
        std::string filename_exact = "test" + std::to_string(exact_count) + "_exact.out";
        WriteToFile(directory_exact, filename_exact, subgraphs_Exact[0], subgraphs_Exact[1], commonEdges_Exact);

        // print the result expected in the output file
        // FIRST LINE : number of common edges between the two subgraphs
        cout << subgraphs_Exact[0].size()+subgraphs_Exact[1].size() << " " << commonEdges_Exact << endl;
        // SECOND LINE : vertices of the first subgraph
        cout << "V1 : ";
        for(const int& element : subgraphs_Exact[0]){
            cout << element << " ";
        }
        cout << endl;
        // THIRD LINE : vertices of the second subgraph
        cout << "V2 : ";
        for(const int& element : subgraphs_Exact[1]){
            cout << element << " ";
        }
        cout << endl;
#endif

        N += step;
        iteration_exact++;
    }
#endif


/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Constructive \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */

#ifdef CONSTRUCTIVE

    cout << "#---------------- CONSTRUCTIVE ----------------#" << endl;

/* #==========# Initialize the parameters that will be used #==========# */

/* PARAMETERS FOR THE ALGORTIHM */
    // Number of vertices
    N = N_base;
    // Initialize the graph
    GraphAdjacencyList graph_Constructive(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_Constructive;

/* PARAMETERS FOR THE FILE .out */
    int commonEdges_Constructive;
    int constructive_count;

/* PARAMETERS FOR THE CSV FILE */
    // Name of the csv file
    const string outputFileNameConstructive = "../instances/constructive/execution_times_Constructive.csv";
    // Open the file to write in
    ofstream outputFileConstructive(outputFileNameConstructive);
    if (!outputFileConstructive.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }

/* PARAMETERS TO PRINT FOR THE TEST */
    int iteration_constructive = 1;

/* #==========# Execution of the local search algorithm #==========# */
    while (N <= maxIterations) {

        // Reset the graph and rebuild it with a new number of vertices N
        graph_Constructive.resetAndRebuild(N, probEdges);
        cout << "ITERATION " << iteration_constructive << " - " << N << " points - ";

        // start of the execution time
        auto startConstructive = chrono::high_resolution_clock::now();
        // Applique l'heuristique constructive au graphe
        subgraphs_Constructive = ConstructiveHeuristic(graph_Constructive);
        // We put the result of the local search algorithm in a var because we need it to compute the number of common edges for the output file
        cout << "CONSTRUCTIVE - ";

        // end of the execution time
        auto endConstructive = chrono::high_resolution_clock::now();
        int temps_execution_constructive = std::chrono::duration_cast<chrono::microseconds>(endConstructive - startConstructive).count();
        cout << "Time taken by function: " << temps_execution_constructive << " microseconds - " ;
        // write the number of vertices and the execution time in the csv file
        outputFileConstructive << N << ", " << temps_execution_constructive << endl;
        cout << "FIN" << endl;

/* Writing the result in the output file */
#ifdef OUTPUT
        // compute the number of common edges between the two subgraphs
        commonEdges_Constructive = calculEdgeCommun(graph_Constructive,subgraphs_Constructive);
        // Count the number of output files in the directory
        constructive_count = CountOutFilesInDirectory("../instances/constructive");

        // Directory to save the file
        std::string directory_local = "../instances/constructive/";
        // Write the result to the output file
        std::string filename_local = "test" + std::to_string(constructive_count) + "_constructive.out";
        WriteToFile(directory_local, filename_local, subgraphs_Constructive[0], subgraphs_Constructive[1], commonEdges_Constructive);



        // print the result expected in the output file
        // FIRST LINE : number of common edges between the two subgraphs
        cout << subgraphs_Constructive[0].size()+subgraphs_Constructive[1].size() << " " << commonEdges_Constructive << endl;
        // SECOND LINE : vertices of the first subgraph
        cout << "V1 : ";
        for(const int& element : subgraphs_Constructive[0]){
            cout << element << " ";
        }
        cout << endl;
        // THIRD LINE : vertices of the second subgraph
        cout << "V2 : ";
        for(const int& element : subgraphs_Constructive[1]){
            cout << element << " ";
        }
        cout << endl;
#endif

        N += step;
        iteration_constructive++;
    }
#endif

/* ---------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Local Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ---------------------------------------------------------------------------------- */

#ifdef LOCAL

    cout << "#---------------- LOCAL SEARCH ----------------#" << endl;

/* #==========# Initialize the parameters that will be used #==========# */

/* PARAMETERS FOR THE ALGORTIHM */
    // Number of vertices
    N = N_base;
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
    const string outputFileNameLocal = "../instances/local_search/execution_times_LocalSearch.csv";
    // Open the file to write in
    ofstream outputFileLocal(outputFileNameLocal);
    if (!outputFileLocal.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }

/* PARAMETERS TO PRINT FOR THE TEST */
    int iteration_local = 1;

/* #==========# Execution of the local search algorithm #==========# */
    while (N <= maxIterations) {

        // Reset the graph and rebuild it with a new number of vertices N
        graph_LocalSearch.resetAndRebuild(N, probEdges);
        cout << "ITERATION " << iteration_local << " - " << N << " points - ";
        // Applique l'heuristique constructive au graphe
        subgraphs_Const = ConstructiveHeuristic(graph_LocalSearch);

        // start of the execution time
        auto startLocal = chrono::high_resolution_clock::now();
        subgraphs_LocalSearch = LocalSearch(graph_LocalSearch, subgraphs_Const);
// We put the result of the local search algorithm in a var because we need it to compute the number of common edges for the output file

        cout << "LOCAL - ";

        // end of the execution time
        auto endLocal = chrono::high_resolution_clock::now();
        int temps_execution_local = std::chrono::duration_cast<chrono::microseconds>(endLocal - startLocal).count();

        cout << "Time taken by function: " << temps_execution_local << " microseconds - " ;

        // write the number of vertices and the execution time in the csv file
        outputFileLocal << N << ", " << temps_execution_local << endl;

        commonEdges_LocalSearch = calculEdgeCommun(graph_LocalSearch,subgraphs_LocalSearch);

        cout << commonEdges_LocalSearch << " - FIN" << endl;

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

        N += step;
        iteration_local++;
    }
#endif

/* --------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// Tabu Search \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* --------------------------------------------------------------------------------- */

#ifdef TABU

    cout << "#---------------- TABU SEARCH ----------------#" << endl;

/* #==========# Initialize the parameters that will be used #==========# */

/* PARAMETERS FOR THE ALGORTIHM */
    // Number of vertices
    N = N_base;
    // Initialize the graph
    GraphAdjacencyList graph_TabuSearch(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_TabuSearch;

/* PARAMETERS FOR THE FILE .out */
    int commonEdges_TabuSearch;
    int tabu_count;

/* PARAMETERS FOR THE CSV FILE */
    // Name of the csv file
    const string outputFileNameTabu = "../instances/tabu_search/execution_times_TabuSearch.csv";
    // Open the file to write in
    ofstream outputFileTabu(outputFileNameTabu);
    if (!outputFileTabu.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }

/* PARAMETERS TO PRINT FOR THE TEST */
    int iteration_tabu = 1;

/* #==========# Execution of the local search algorithm #==========# */
    while (N <= maxIterations) {

        // Reset the graph and rebuild it with a new number of vertices N
        graph_TabuSearch.resetAndRebuild(N, probEdges);
        cout << "ITERATION " << iteration_tabu << " - " << N << " points - ";

        // start of the execution time
        auto startTabu = chrono::high_resolution_clock::now();
        subgraphs_TabuSearch = TabuSearch(graph_TabuSearch);
// We put the result of the tabu search algorithm in a var because we need it to compute the number of common edges for the output file

        cout << "TABU - ";

        // end of the execution time
        auto endTabu = chrono::high_resolution_clock::now();
        int temps_execution_tabu = std::chrono::duration_cast<chrono::microseconds>(endTabu - startTabu).count();

        cout << "Time taken by function: " << temps_execution_tabu << " microseconds - " ;

        // write the number of vertices and the execution time in the csv file
        outputFileTabu << N << ", " << temps_execution_tabu << endl;

        commonEdges_TabuSearch = calculEdgeCommun(graph_TabuSearch,subgraphs_TabuSearch);

        cout << commonEdges_TabuSearch << " - FIN" << endl;

/* Writing the result in the output file */
#ifdef OUTPUT
        // compute the number of common edges between the two subgraphs
        commonEdges_TabuSearch = calculEdgeCommun(graph_LocalSearch,subgraphs_TabuSearch);
        // Count the number of output files in the directory
        tabu_count = CountOutFilesInDirectory("../instances/tabu_search");

        // Directory to save the file
        std::string directory_tabu = "../instances/tabu_search/";
        // Write the result to the output file
        std::string filename_tabu = "test" + std::to_string(tabu_count) + "_tabu_search.out";
        WriteToFile(directory_tabu, filename_tabu, subgraphs_TabuSearch[0], subgraphs_TabuSearch[1], commonEdges_TabuSearch);

        // print the result expected in the output file
        // FIRST LINE : number of common edges between the two subgraphs
        cout << subgraphs_TabuSearch[0].size()+subgraphs_TabuSearch[1].size() << " " << commonEdges_TabuSearch << endl;
        // SECOND LINE : vertices of the first subgraph
        cout << "V1 : ";
        for(const int& element : subgraphs_TabuSearch[0]){
            cout << element << " ";
        }
        cout << endl;
        // THIRD LINE : vertices of the second subgraph
        cout << "V2 : ";
        for(const int& element : subgraphs_TabuSearch[1]){
            cout << element << " ";
        }
        cout << endl;
#endif

        N += step;
        iteration_tabu++;
    }

#endif

/* ----------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-// All algorithm \\-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ----------------------------------------------------------------------------------- */

#ifdef ALL

/* PARAMETERS FOR THE ALGORTIHM */
    // Number of vertices
    N = N_base;
    //Creat the graph for all tests
    GraphAdjacencyList graphAll(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_ExactALL;
    vector<vector<int>> subgraphs_ConstructiveALL;
    vector<vector<int>> subgraphs_LocalSearchALL;
    vector<vector<int>> subgraphs_TabuSearchALL;

/* PARAMETERS FOR THE CSV FILE */
    //Create csv files
    const string outputFileNameExactALL = "../instances/exact/execution_times_Exact-ALL.csv";
    const string outputFileNameConstructiveALL = "../instances/constructive/execution_times_Constructive-ALL.csv";
    const string outputFileNameLocalALL = "../instances/local_search/execution_times_LocalSearch-ALL.csv";
    const string outputFileNameTabuALL = "../instances/tabu_search/execution_times_Tabu-ALL.csv";
    const string outputEdgesFileNameExactALL = "../instances/exact/edges_Exact-ALL.csv";
    const string outputEdgesFileNameConstructiveALL = "../instances/constructive/edges_Constructive-ALL.csv";
    const string outputEdgesFileNameLocalALL = "../instances/local_search/edges_LocalSearch-ALL.csv";
    const string outputEdgesFileNameTabuALL = "../instances/tabu_search/edges_Tabu-ALL.csv";

    // Open all files to write in
    ofstream outputFileExactALL(outputFileNameExactALL);
    if (!outputFileExactALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputFileLocalALL(outputFileNameLocalALL);
    if (!outputFileLocalALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputFileConstructiveALL(outputFileNameConstructiveALL);
    if (!outputFileConstructiveALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputFileTabuALL(outputFileNameTabuALL);
    if (!outputFileTabuALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputEdgesFileExactALL(outputEdgesFileNameExactALL);
    if (!outputEdgesFileExactALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputEdgesFileLocalALL(outputEdgesFileNameLocalALL);
    if (!outputEdgesFileLocalALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputEdgesFileConstructiveALL(outputEdgesFileNameConstructiveALL);
    if (!outputEdgesFileConstructiveALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }
    ofstream outputEdgesFileTabuALL(outputEdgesFileNameTabuALL);
    if (!outputEdgesFileTabuALL.is_open()) {
        cerr << "Error: Cannot open CSV file for writing." << endl;
        return 1;
    }

    int iteration_ALL = 1;

    cout << "------------------------------------------------" << endl;
    while (N <= maxIterations) {
        // Reset the graph and rebuild it with a new number of vertices N
        graphAll.resetAndRebuild(N, probEdges);

        /*----------EXACT----------*/

        //Start the chrono
        auto startExact = chrono::high_resolution_clock::now();
        //Execute the function
        vector<int> tabVertices = {};
        for (int i = 0; i < graphAll.V; ++i) {
            tabVertices.push_back(i);
        }
        int min_cut_exact = numeric_limits<int>::max();
        vector<int> best = {};
        subgraphs_ExactALL = Exact_Main(graphAll);

        //Stop the chrono
        auto endExact = chrono::high_resolution_clock::now();
        int temps_execution_exact = std::chrono::duration_cast<chrono::microseconds>(endExact - startExact).count();

        cout << endl << "ITERATION " << iteration_ALL << " - " << N << " points - EXACT - ";
        cout << "Time taken by function: " << temps_execution_exact << " microseconds " ;
        auto edgesExact = calculEdgeCommun(graphAll,subgraphs_ExactALL);
        cout << " - " << edgesExact << " edges" << endl;
        // Write the informations in the CSV file
        outputFileExactALL << N << ", " << temps_execution_exact << endl;
        outputEdgesFileExactALL << N << ", " << edgesExact << endl;


        /*----------CONSTRUCTIVE----------*/
        //Start the chrono
        auto startConstructive = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_ConstructiveALL = ConstructiveHeuristic(graphAll);
        //Stop the chrono
        auto endConstructive = chrono::high_resolution_clock::now();
        int temps_execution_constructive = std::chrono::duration_cast<chrono::microseconds>(endConstructive - startConstructive).count();

        cout << endl << "ITERATION " << iteration_ALL << " - " << N << " points - CONSTRUCTIVE - ";
        cout << "Time taken by function: " << temps_execution_constructive << " microseconds " ;
        auto edgesConstructive = calculEdgeCommun(graphAll,subgraphs_ConstructiveALL);
        cout << " - " << edgesConstructive << " edges" << endl;
        // Write the informations in the CSV file
        outputFileConstructiveALL << N << ", " << temps_execution_constructive << endl;
        outputEdgesFileConstructiveALL << N << ", " << edgesConstructive << endl;


        /*----------LOCAL-SEARCH----------*/
        //Start the chrono
        auto startLocal = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_LocalSearchALL = LocalSearch(graphAll, subgraphs_ConstructiveALL);
        //Stop the chrono
        auto endLocal = chrono::high_resolution_clock::now();
        int temps_execution_local = std::chrono::duration_cast<chrono::microseconds>(endLocal - startLocal).count();

        cout << endl << "ITERATION " << iteration_ALL << " - " << N << " points - LOCAL - ";
        cout << "Time taken by function: " << temps_execution_local << " microseconds " ;

        auto edgesLocal = calculEdgeCommun(graphAll,subgraphs_LocalSearchALL);
        cout << " - " << edgesLocal << " edges" << endl;
        // Write the informations in the CSV file
        outputFileLocalALL << N << ", " << temps_execution_local << endl;
        outputEdgesFileLocalALL << N << ", " << edgesLocal << endl;


        /*----------TABU-SEARCH----------*/
        //Start the chrono
        auto startTabu = chrono::high_resolution_clock::now();
        //Execute the function
        subgraphs_TabuSearchALL = TabuSearch(graphAll);
        //Stop the chrono
        auto endTabu = chrono::high_resolution_clock::now();
        int temps_execution_tabu = std::chrono::duration_cast<chrono::microseconds>(endTabu - startTabu).count();

        cout << "ITERATION " << iteration_ALL << " - " << N << " points - TABU - ";
        cout << "Time taken by function: " << temps_execution_tabu << " microseconds " ;

        auto edgesTabu = calculEdgeCommun(graphAll,subgraphs_TabuSearchALL);
        cout << " - " << edgesTabu << " edges" << endl;
        // Write the informations in the CSV file
        outputFileTabuALL << N << ", " << temps_execution_tabu << endl;
        outputEdgesFileTabuALL << N << ", " << edgesTabu << endl;


        /*----------PARAMETERS----------*/
        iteration_ALL++;
        N += step;
    }
#endif

/* ----------------------------------------------------------------------------------- */
/* <-_-_-_-_-_-_-_-_-_-_-_-_-// All algorithm with in files \\-_-_-_-_-_-_-_-_-_-_-_-_-> */
/* ----------------------------------------------------------------------------------- */



/*----------FILE IN (CHOOSE ON TO EXECUTE)----------*/
    string file = "../instances/new_instances/test20_25.in";
    string fileNameIn = "test20_25";

#ifdef EXACT_WITH_IN_FILES
/*----------EXACT----------*/
    /* PARAMETERS FOR THE ALGORTIHM */
    // Initialize the graph
    GraphAdjacencyList graph_Exact_In(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_Exact_In;
    //Rebuild the graph
    graph_Exact_In.rebuildWithInFile(file);
    //Execute the algorithm
    subgraphs_Exact_In = Exact_Main(graph_Exact_In);

    /* PARAMETERS FOR THE FILE .out */
    int commonEdges_Exact_in;

    /* Writing the result in the output file */
    // compute the number of common edges between the two subgraphs
    commonEdges_Exact_in = calculEdgeCommun(graph_Exact_In, subgraphs_Exact_In);

    // Directory to save the file
    std::string directory_exact_in = "../instances/exact/";
    // Write the result to the output file
    std::string filename_exact_in = fileNameIn + "_exact.out";
    WriteToFile(directory_exact_in, filename_exact_in, subgraphs_Exact_In[0], subgraphs_Exact_In[1], commonEdges_Exact_in);

    // print the result expected in the output file
    // FIRST LINE : number of common edges between the two subgraphs
    cout << "------EXACT------" << endl;
    cout << subgraphs_Exact_In[0].size()+subgraphs_Exact_In[1].size() << " " << commonEdges_Exact_in << endl;
    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : subgraphs_Exact_In[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : subgraphs_Exact_In[1]){
        cout << element << " ";
    }
    cout << endl;
#endif

#ifdef CONSTRUCTIVE_WITH_IN_FILES
/*----------CONSTRUCTIVE-HEURISTIC----------*/
    /* PARAMETERS FOR THE ALGORTIHM */
    // Initialize the graph
    GraphAdjacencyList graph_ConstructiveIn(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_Constructive_In;
    //Rebuild the graph
    graph_ConstructiveIn.rebuildWithInFile(file);
    //Execute the algorithm
    subgraphs_Constructive_In = ConstructiveHeuristic(graph_ConstructiveIn);

    /* PARAMETERS FOR THE FILE .out */
    int commonEdges_Constructive_in;

    /* Writing the result in the output file */
    // compute the number of common edges between the two subgraphs
    commonEdges_Constructive_in = calculEdgeCommun(graph_ConstructiveIn,subgraphs_Constructive_In);

    // Directory to save the file
    std::string directory_constructive_in = "../instances/constructive/";
    // Write the result to the output file
    std::string filename_constructive_in = fileNameIn + "_constructive.out";
    WriteToFile(directory_constructive_in, filename_constructive_in, subgraphs_Constructive_In[0], subgraphs_Constructive_In[1], commonEdges_Constructive_in);

    // print the result expected in the output file
    // FIRST LINE : number of common edges between the two subgraphs
    cout << "------CONSTRUCTIVE------" << endl;
    cout << subgraphs_Constructive_In[0].size()+subgraphs_Constructive_In[1].size() << " " << commonEdges_Constructive_in << endl;
    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : subgraphs_Constructive_In[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : subgraphs_Constructive_In[1]){
        cout << element << " ";
    }
    cout << endl;
#endif

#ifdef LOCAL_WITH_IN_FILES
/*----------LOCAL-SEARCH----------*/
    /* PARAMETERS FOR THE ALGORTIHM */
    // Initialize the graph
    GraphAdjacencyList graph_LocalSearchIn(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_ConstIn;
    vector<vector<int>> subgraphs_LocalSearchIn;
    // Reset the graph and rebuild it with a new number of vertices N
    graph_LocalSearchIn.rebuildWithInFile(file);
    // Execute the algorithm
    subgraphs_ConstIn = ConstructiveHeuristic(graph_LocalSearchIn);
    subgraphs_LocalSearchIn = LocalSearch(graph_LocalSearchIn, subgraphs_ConstIn);

    /* PARAMETERS FOR THE FILE .out */
    int commonEdges_LocalSearch_in;

    /* Writing the result in the output file */
    // compute the number of common edges between the two subgraphs
    commonEdges_LocalSearch_in = calculEdgeCommun(graph_LocalSearchIn,subgraphs_LocalSearchIn);

    // Directory to save the file
    std::string directory_local_in = "../instances/local_search/";
    // Write the result to the output file
    std::string filename_local_in = fileNameIn + "_local_search.out";
    WriteToFile(directory_local_in, filename_local_in, subgraphs_LocalSearchIn[0], subgraphs_LocalSearchIn[1], commonEdges_LocalSearch_in);

    // print the result expected in the output file
    cout << "------LOCAL------" << endl;
    // FIRST LINE : number of common edges between the two subgraphs
    cout << subgraphs_LocalSearchIn[0].size()+subgraphs_LocalSearchIn[1].size() << " " << commonEdges_LocalSearch_in << endl;
    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : subgraphs_LocalSearchIn[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : subgraphs_LocalSearchIn[1]){
        cout << element << " ";
    }
    cout << endl;
#endif

#ifdef TABU_WITH_IN_FILES
/*----------TABU-SEARCH----------*/
    /* PARAMETERS FOR THE ALGORTIHM */
    // Initialize the graph
    GraphAdjacencyList graph_TabuSearchIn(0);
    // Initialize the subgraphs
    vector<vector<int>> subgraphs_TabuSearchIn;
    //Rebuild the graph
    graph_TabuSearchIn.rebuildWithInFile(file);
    //Execute the algorithm
    subgraphs_TabuSearchIn = TabuSearch(graph_TabuSearchIn);

    /* PARAMETERS FOR THE FILE .out */
    int commonEdges_TabuSearch_in;

    /* Writing the result in the output file */
    // compute the number of common edges between the two subgraphs
    commonEdges_TabuSearch_in = calculEdgeCommun(graph_TabuSearchIn,subgraphs_TabuSearchIn);

    // Directory to save the file
    std::string directory_tabu_in = "../instances/tabu_search/";
    // Write the result to the output file
    std::string filename_tabu_in = fileNameIn + "_tabu_search.out";
    WriteToFile(directory_tabu_in, filename_tabu_in, subgraphs_TabuSearchIn[0], subgraphs_TabuSearchIn[1], commonEdges_TabuSearch_in);

    // print the result expected in the output file
    cout << "------TABU------" << endl;
    // FIRST LINE : number of common edges between the two subgraphs
    cout << subgraphs_TabuSearchIn[0].size()+subgraphs_TabuSearchIn[1].size() << " " << commonEdges_TabuSearch_in << endl;
    // SECOND LINE : vertices of the first subgraph
    cout << "V1 : ";
    for(const int& element : subgraphs_TabuSearchIn[0]){
        cout << element << " ";
    }
    cout << endl;
    // THIRD LINE : vertices of the second subgraph
    cout << "V2 : ";
    for(const int& element : subgraphs_TabuSearchIn[1]){
        cout << element << " ";
    }
    cout << endl;
#endif

    cout << endl << " END OF THE PROGRAM, THANKS FOR USING IT ! :D " << endl;
    return 0;
}
