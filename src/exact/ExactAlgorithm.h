#ifndef GRAPHTHEORYPROJECT_GROUP2_EXACTALGORITHM_H
#define GRAPHTHEORYPROJECT_GROUP2_EXACTALGORITHM_H



#include <bits/stdc++.h>
#include "../model/GraphAdjacencyList.h"
using namespace std;

void affiche_vector(vector <int> v);
void powerSet(GraphAdjacencyList G, vector<int> vertices, int& min_cut, vector<int>& best, int index = -1, vector<int> curr = {});
vector<int> deduire_subgraph2(vector<int> vertices, vector<int> subgraph1);


#endif //GRAPHTHEORYPROJECT_GROUP2_EXACTALGORITHM_H
