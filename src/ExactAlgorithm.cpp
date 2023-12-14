#include "ExactAlgorithm.h"
#include "GraphAdjacencyList.h"

void affiche_vector(vector <int> v){
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
}

vector<int> deduire_subgraph2(vector<int> vertices, vector<int> subgraph1){
    vector<int> subgraph2 = {};
    bool ajout;
    for (const auto &elemVertices : vertices) {
        ajout = true;
        for (const auto &elemSubgraph1 : subgraph1) {
            if (elemSubgraph1 == elemVertices) {
                ajout = false;
            }
        }
        if (ajout){
            subgraph2.push_back(elemVertices);
        }
    }
    return subgraph2;
}

void powerSet(GraphAdjacencyList G, vector<int> vertices, int& min_cut, vector<int>& best, int index, vector<int> curr)
{
    int n = vertices.size();

    // base case
    if (index == n)
        return;

    // First print current subset
    if (curr.size() == n/2) {
        affiche_vector(curr);
        cout << "\n";

        vector<vector<int>> subgraphs;
        subgraphs.push_back(curr);
        subgraphs.push_back(deduire_subgraph2(vertices, curr));

        int cut = calculEdgeCommun(G,subgraphs);
        cout << "Number of edges : " << cut << endl;

        if (cut < min_cut){
            min_cut = cut;
            best.clear();
            best = curr;
        }
    }

    // Try appending remaining characters
    // to current subset
    for (int i = index + 1; i < n; i++) {

        curr.push_back(vertices[i]);
        powerSet(G, vertices, min_cut, best, i, curr);

        // Once all subsets beginning with
        // initial "curr" are printed, remove
        // last character to consider a different
        // prefix of subsets.
        auto last = curr.end() - 1;
        curr.erase(last);
    }
    return;
}
