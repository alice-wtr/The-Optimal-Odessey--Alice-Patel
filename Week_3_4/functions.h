#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "graph.h"

using namespace std;


void TSPBruteForce(Graph &map, int& optimal_cost, vector<int>& tour, vector<int>& nodes);
void TSPHeldKarp(Graph &map, int& optimal_cost, vector<int>& tour, vector<int>& nodes);
void astar_euclidean(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time);
void astar_manhattan(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time);
void dijkstra(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time);
int eu(Node a, Node b);
int mn(Node a, Node b);
int dj(Node a, Node b);

#endif