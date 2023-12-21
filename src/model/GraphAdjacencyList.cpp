#include "GraphAdjacencyList.h"

/* //=========\\ Class GraphAdjacencyList //=========\\ */

/* <------# Constructor #------> */
GraphAdjacencyList::GraphAdjacencyList(int vertices) : V(vertices) {
    adjacencyList.resize(vertices);
}

/* <------# Methods #------> */

void GraphAdjacencyList::resetAndRebuild(int vertices, int probEdges) {
/*
 * INPUT : an integer vertices representing the number of vertices and an integer probEdges representing the probability of edges
 * OUTPUT : none
 * FUNCTION : reset the graph and rebuild it with a new number of vertices
 */
    V = vertices;
    adjacencyList.resize(vertices);

// Add edges with a probability of probEdges
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {

            if (rand() % 100 < probEdges) {
                if (i != j && !isEdge(i, j)) {
                    addEdge(i, j);
                }
            }
        }
    }
}

void GraphAdjacencyList::rebuildWithInFile(const string fileName) {
/*
 * INPUT : an in file with the number of vertices and edges follow by all the edges
 * OUTPUT : none
 * FUNCTION : reset the graph and rebuild it with the csv information
 */
    ifstream file(fileName);
    if(!file.is_open()){
        std::cerr << "Error: Cannot open file for writing." << std::endl;
        return;
    }

    // Reading of the first line
    int numberVertices, numberEdges;
    file >> numberVertices >> numberEdges;
    //Add the number of vertices in the struct of the graph
    V = numberVertices;
    adjacencyList.resize(numberVertices);

    //reading the second line
    //vector<vector<int>> allEdges;
    int edge1, edge2;
    for(int i=0; i<numberEdges; i++){
        file >> edge1 >> edge2;
        //allEdges.push_back({edge1,edge2});
        addEdge(edge1, edge2);
    }

    file.close();
}

void GraphAdjacencyList::addEdge(int v, int w) {
/*
 * INPUT : two integers v and w representing two vertices
 * OUTPUT : none
 * FUNCTION : add an edge between the vertices v and w
 */
    adjacencyList[v].push_back(w);
    adjacencyList[w].push_back(v);
}

bool GraphAdjacencyList::isEdge(int v, int w){
/*
 * INPUT : two integers v and w representing two vertices
 * OUTPUT : boolean
 * FUNCTION : check if there is an edge between the vertices v and w
 */
    for(int i=0; i<adjacencyList[v].size(); i++){
        if(adjacencyList[v][i] == w){
            return true;
        }
    }
    return false;
}

void GraphAdjacencyList::printGraph() {
/*
 * INPUT : none
 * OUTPUT : none
 * FUNCTION : print the graph
 */
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " :";
        for (const int &neighbor : adjacencyList[i]) {
            cout << " " << neighbor ;
        }
        cout << endl;
    }
}

int GraphAdjacencyList::degree(int v) {
/*
 * INPUT : a vertex v
 * OUTPUT : an integer
 * FUNCTION : compute the degree of the vertex v
 */
    return adjacencyList[v].size();
}

vector<int> GraphAdjacencyList::allDegrees(){
/*
 * INPUT : none
 * OUTPUT : a vector of integers
 * FUNCTION : compute the degree of all the vertices
 */
    vector<int> tab;
    for(int i=0; i<V; i++){
        tab.push_back(degree(i));
    }
    return tab;
}

int GraphAdjacencyList::InOutDegree(int v, vector<int> V1){
/*
 * INPUT : an integer v representing a vertex and a vector of vertices V1 representing a subgraph
 * OUTPUT : an integer
 * FUNCTION : compute the in or out degrees of the vertex v depending on if v is in V1 or not
 */
    /*cout << "degree ";*/
    int count = 0;
    for(int i=0; i<V1.size(); i++){
        if(isEdge(v, V1[i])){
            /*cout << V1[i] << " - ";*/
            count++;
        }
    }
    /*cout << endl;*/
    return count;

}

/* <------# Functions #------> */

int calculEdgeCommun(GraphAdjacencyList G, vector<vector<int>> subgraphs){
/*
 * INPUT : a graph G and a vector of two subgraphs
 * OUTPUT : an integer
 * FUNCTION : compute the number of common edges between the two subgraphs
 */
    vector<int> V1 = subgraphs[0];
    vector<int> V2 = subgraphs[1];
    int som = 0;
    for(int i=0; i<V1.size(); i++){
        for(const int &neighbor : G.adjacencyList[V1[i]]){
            for(int j=0; j<V2.size(); j++){
                if(neighbor == V2[j]){
                    som ++;
                }
            }
        }
    }
    return som;
}

void WriteToFile(const std::string& directory, const std::string& filename, const std::vector<int>& V1, const std::vector<int>& V2, int commonEdges) {
/*
 * INPUT : a directory, a filename, two vectors V1 and V2, representing two subgraphs and the number of common edges between the two subgraphs
 * OUTPUT : none
 * FUNCTION : create a file in the asked directory with the asked filename
 *            write in it the size of the graph and the number of common edges between the two subgraphs V1 and V2 and the two subgraphs
 */

    // Create a file in the asked directory with the asked filename
    ofstream outFile(directory + "/"+ filename);

    if (outFile.is_open()) {
        // Write in the first line: the size of the graph and the number of common edges between the two subgraphs V1 and V2
        outFile << V1.size() + V2.size() << " " << commonEdges << "\n";

        // Write in the second line: all vertices in V1
        for (int X1 = 0; X1 < V1.size(); X1++) {
            outFile << V1[X1];
            // Allows to not write a space after the last vertex
            if (X1 < V1.size() - 1)
                outFile << " ";
        }
        outFile << "\n";

        // Write in the third line: all vertices in V2
        for (int X2 = 0; X2 < V2.size(); X2++) {
            outFile << V2[X2];
            // Allows to not write a space after the last vertex
            if (X2 < V2.size() - 1)
                outFile << " ";
        }
        outFile << "\n";

        outFile.close();
    }
    else {
        // If the file cannot be opened, we display an error message
        cerr << "Unable to open file: " << directory << filename << endl;
    }
}


int CountOutFilesInDirectory(const std::string& directoryPath) {
/*
 * INPUT : a directory path
 * OUTPUT : an integer
 * FUNCTION : count the number of output files in the directory
 */
    // Initialize the counter
    int count = 0;

    // Try to open the directory
    try {
        // For each entry in the directory
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            // If the entry is a regular file and has the extension ".out", we increment the counter
            if (entry.is_regular_file() && entry.path().extension() == ".out") {
                count++;
            }
        }
    }
    // If the directory cannot be opened, we display an error message
    catch (const std::exception& e) {
        std::cerr << "Error reading directoryy : " << e.what() << std::endl;
    }

    return count;
}