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

void TSPBruteForce(Graph &map, int& optimal_cost, vector<int>& tour, vector<int>& nodes) {

    
    sort(nodes.begin(), nodes.end());
    int l = nodes.size();

    do {

        int path = 0;
        for(int i = 0; i<l-1; i++){
            path = path + map.dist[nodes[i]][nodes[i+1]];
        }
        path = path + map.dist[nodes[l-1]][nodes[0]];

        if(path < optimal_cost) {optimal_cost = path; tour = nodes;}

        
    } while (next_permutation(nodes.begin(), nodes.end()));   
    
    tour.push_back(tour[0]);
}

//apologies for the excessive comments, this algo was hard to understand and i am certain i will forget next time i try to read it
//(she says, as if anyone else is going to read it)
void TSPHeldKarp(Graph &map, int& optimal_cost, vector<int>& tour, vector<int>& nodes){

    //dp is basically dp[which cities have been visited][current city] note first index is integer. if it's 100 then it will be stored simply as 4 not as integer hundred

    int n = nodes.size();
    int been = (1<<n);

    vector<vector<int>> dp(1 << n, vector<int>(n, 1e9));
    vector<vector<int>> parent(1<<n, vector<int>(n, -1));
    dp[1][0] = 0;
    parent[1][0] = -2;

    for(int i = 0; i<been; i++){
        for(int j = 0; j<n; j++) {


            //this is technically not necessary because every state would be visited by the previous layer of seeing. i.e. we start with 1 city and it 'next wala loop' 
            //would ensure all masks with 2 city are not infinity. 2 cities would ensure all 3 city masks are non infinity etc.

            //this is for the case the graph is not connected 
            if(dp[i][j] == 1e9) continue;

            //if j is not in mask that's an impossible situation. why would it end in j if j has not been visited? so we skip those cases
            if (!(i & (1 << j))) continue;

            for(int next=0; next<n; next++){
                // if next is 3 and n is 5 1<<next = 00101 and suppose i is 10101. then & of both is 00100 which is non zero, hence the city has been visited
                if((1<<next)&i) continue;

                if(dp[(1<<next)|i][next] > dp[i][j] + map.dist[nodes[j]][nodes[next]]) {
                    dp[(1<<next)|i][next] = dp[i][j] + map.dist[nodes[j]][nodes[next]];
                    parent[(1<<next)|i][next] = j;

                }

                //dp[(1<<next)|i][next] = min(dp[(1<<next)|i][next], dp[i][j] + map.dist[nodes[j]][nodes[next]]);
            }

        }
    }

    int ans = 1e9;
    int all_been = (1<<n) - 1;
    
    int last = -1;

    for (int i = 0; i < n; i++) {
        int cost = dp[all_been][i] + map.dist[nodes[i]][nodes[0]];
        if (cost < ans) {
            ans = cost;
            last = i;
        }
    }

    optimal_cost = ans;

    int mask = all_been;
    int city = last;

    while (city != -2)
    {
        tour.push_back(nodes[city]);
        int prev = parent[mask][city];
        mask ^= (1 << city);
        city = prev;
    }
    reverse(tour.begin(), tour.end());
    tour.push_back(nodes[0]);
}

