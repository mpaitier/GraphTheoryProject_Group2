#include "TabuSearch.h"

vector<vector<int>> TabuSearch(GraphAdjacencyList &graph) {
/*
 * INPUT : a graph
 * OUTPUT : two subgraphs V1 and V2
 * FUNCTION : apply the tabu search heuristic to the graph
 */
    // to have different random numbers at each execution
    srand(time(NULL));

    // create two subgraphs: best solution and current solution, result of the constructive heuristic
    vector<vector<int>> bestSolution = ConstructiveHeuristic(graph);
    vector<vector<int>> currentSolution = bestSolution;

    // initialize the index of the vertex X1 and X2
    int X1, X2;

    // initialize the parameters for the break condition
    int i = 0;
    int j = 0;
    int Max_Fail = 20;
    int Max_Try = 100;

    // initialize the tabu list
    // parameters that will contain the pair of vertices that we will swap
    vector<int> Pair1;
    vector<int> Pair2;

    vector<vector<int>> TabuList;

    // while the break conditions are not satisfied, we continue the tabu search
    while( i < Max_Fail && j < Max_Try) {

        currentSolution = bestSolution;

        // choose two vertices X1 and X2 randomly
        X1 = rand() % (graph.V / 2);
        X2 = rand() % (graph.V / 2);

        Pair1 = {X1, X2};
        Pair2 = {X2, X1};

        // check if the pair of vertices is in the tabu list
        if (find(TabuList.begin(), TabuList.end(), Pair1) != TabuList.end() || find(TabuList.begin(), TabuList.end(), Pair2) != TabuList.end()) {
            // if the pair of vertices is in the tabu list, then we don't do anything
        }
        else {
            // if the pair of vertices is not in the tabu list, then we swap the two vertices
            int temp = currentSolution[0][X1];
            currentSolution[0][X1] = currentSolution[1][X2];
            currentSolution[1][X2] = temp;

            // add the pair of vertices to the tabu list
            TabuList.push_back(Pair1);
            TabuList.push_back(Pair2);

            // update the current solution
            auto newCurrentSolution = LocalSearch(graph, currentSolution);


            if(calculEdgeCommun(graph, newCurrentSolution) < calculEdgeCommun(graph, bestSolution)){

                // if the current solution is better than the best solution, then we update the best solution
                bestSolution = newCurrentSolution;

                // success found, so we reset the number of try until success
                i = 0;
            }

        }

        // the number of try is incremented
        j++;
        i++;
    }

    // return the best solution
    return bestSolution;
}