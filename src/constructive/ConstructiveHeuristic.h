#ifndef GRAPHTHEORYPROJECT_GROUP2_CONSTRUCTIVEHEURISTIC_H
#define GRAPHTHEORYPROJECT_GROUP2_CONSTRUCTIVEHEURISTIC_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "../model/GraphAdjacencyList.h"

using namespace std;

vector<vector<int>> ConstructiveHeuristic(GraphAdjacencyList G);
bool valPresent(vector<int> vector, int val);

#endif //GRAPHTHEORYPROJECT_GROUP2_CONSTRUCTIVEHEURISTIC_H
