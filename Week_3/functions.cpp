#include "functions.h"
#include "graph.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include <cmath>
#include <limits>
#include<algorithm>
#include<chrono>


using namespace std;

int eu(Node a, Node b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int mn(Node a, Node b){
    return abs(a.x-b.x) + abs(a.y-b.y);
}

int dj(Node a, Node b){
    return 0;
}

void astar_euclidean(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time) {
    //here's the code for A* with euclidan

    auto start_time = chrono::high_resolution_clock::now();

    priority_queue<pair<int, Node>> frontier;
    vector<vector<int>> distance(map.rows, vector<int>(map.cols, numeric_limits<int>::max()));
    frontier.push({0, start});
    distance[start.x][start.y] = 0; 

    while(frontier.size() != 0) {

        Node node = frontier.top().second;
        
        frontier.pop();
        if (node.so_far != distance[node.x][node.y]) continue;

        if(node.x == goal.x && node.y == goal.y){
            //found
            path_found = true;
            nodes_explored++;
            path_length = node.so_far;
            break;
        }
        nodes_explored++;


        for(auto n: map.get_neighbors(node)) {

                int new_dist = distance[node.x][node.y] + 1;
                if (new_dist < distance[n.x][n.y]) {
                    n.so_far = node.so_far + 1;
                    distance[n.x][n.y] = new_dist;
                    frontier.push({-(new_dist + eu(n, goal)), n});
                }
                
            }
        }


    

    auto end_time = chrono::high_resolution_clock::now();

time = chrono::duration<float, milli>(end_time - start_time).count();

}

void astar_manhattan(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time) {
    //here's the code for A* with euclidan

    auto start_time = chrono::high_resolution_clock::now();

    priority_queue<pair<int, Node>> frontier;
    vector<vector<int>> distance(map.rows, vector<int>(map.cols, numeric_limits<int>::max()));
    frontier.push({0, start});
    distance[start.x][start.y] = 0; 

    while(frontier.size() != 0) {

        Node node = frontier.top().second;
        
        frontier.pop();
        if (node.so_far != distance[node.x][node.y]) continue;

        if(node.x == goal.x && node.y == goal.y){
            //found
            path_found = true;
            nodes_explored++;
            path_length = node.so_far;
            break;
        }
        nodes_explored++;


        for(auto n: map.get_neighbors(node)) {

                int new_dist = distance[node.x][node.y] + 1;
                if (new_dist < distance[n.x][n.y]) {
                    n.so_far = node.so_far + 1;
                    distance[n.x][n.y] = new_dist;
                    frontier.push({-(new_dist + mn(n, goal)), n});
                }
                
            }
        }


    

auto end_time = chrono::high_resolution_clock::now();

time = chrono::duration<float, milli>(end_time - start_time).count();

}

void dijkstra(Graph& map, Node& start, Node& goal, int& nodes_explored, int& path_length, bool& path_found, float& time) {
    //here's the code for A* with euclidan

    auto start_time = chrono::high_resolution_clock::now();

    priority_queue<pair<int, Node>> frontier;
    vector<vector<int>> distance(map.rows, vector<int>(map.cols, numeric_limits<int>::max()));
    frontier.push({0, start});
    distance[start.x][start.y] = 0; 

    while(frontier.size() != 0) {

        Node node = frontier.top().second;
        
        frontier.pop();
        if (node.so_far != distance[node.x][node.y]) continue;

        if(node.x == goal.x && node.y == goal.y){
            //found
            path_found = true;
            nodes_explored++;
            path_length = node.so_far;
            break;
        }
        nodes_explored++;


        for(auto n: map.get_neighbors(node)) {

                int new_dist = distance[node.x][node.y] + 1;
                if (new_dist < distance[n.x][n.y]) {
                    n.so_far = node.so_far + 1;
                    distance[n.x][n.y] = new_dist;
                    frontier.push({-(new_dist + dj(n, goal)), n});
                }
                
            }
        }


    

    auto end_time = chrono::high_resolution_clock::now();

time = chrono::duration<float, milli>(end_time - start_time).count();

}
