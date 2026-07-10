#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include <cmath>
#include <limits>
#include<algorithm>
#include"json.hpp"
#include<chrono>
#include "graph.h"
#include "functions.h"

int INF = 1e9;



using namespace std;

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

    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> parent(1<<n, vector<int>(n, -1));
    dp[1][0] = 0;
    parent[1][0] = -2;

    for(int i = 0; i<been; i++){
        for(int j = 0; j<n; j++) {


            //this is technically not necessary because every state would be visited by the previous layer of seeing. i.e. we start with 1 city and it 'next wala loop' 
            //would ensure all masks with 2 city are not infinity. 2 cities would ensure all 3 city masks are non infinity etc.

            //this is for the case the graph is not connected 
            if(dp[i][j] == INF) continue;

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

    int ans = INF;
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



int main(int argc, char* argv[]){

    if (argc < 4) {
        std::cerr << "Usage: ./{executable} <graph.json> <queries.json> <output.json>\n";
        return 1;
    }

    std::string graph_json_file = argv[1];
    std::string query_json_file = argv[2];
    std::string output_file = argv[3];

    std::ifstream file1(graph_json_file);

    if (!file1.is_open()) {
        std::cerr << "Error: Could not open " << graph_json_file << '\n';
        return 1;
    }

    nlohmann::json graph_json;
    file1 >> graph_json; // reading the graph_json file into json 

	/*!!! Need changes here !!!*/ 
	
	// Create a Graph class that takes the json input
	// and stores the required graph data structures.
	// Remember to include the header file containing the class.
	// Uncomment the line below after implementing the class.
	Graph map(graph_json);

    std::ifstream file2(query_json_file);   

    if (!file2.is_open()) {
        std::cerr << "Error: Could not open " << query_json_file << '\n';
        return 1;
    }

    nlohmann::json query_json;
    file2 >> query_json; // reading the query_json file into json object

    nlohmann::json output_json;

    output_json["meta"] = {{"id", query_json["meta"]["id"]}};
    output_json["results"] = nlohmann::json::array();

    std::string type;

    for(auto event : query_json["events"]){

        type = event["type"];

		/* Refer to the sample code below */
        
        /*if(type == "remove_edge") {
            int edge_id = event["edge_id"];
            bool b = remove_edge(map, edge_id);
            nlohmann::json out;
            out["id"] = event["id"];
            out["done"] = b;
            std::cout << out.dump(4) << std::endl;
            output_json["results"].push_back(out);
        }*/
        
        if(type == "find_path") {
            Node start = {{-1,-1}, 0, {event["start"]["x"], event["start"]["y"]}}; 
            Node goal = {{-1,-1}, -1, {event["goal"]["x"], event["goal"]["y"]}};


            int nodes_explored = 0; 
            int path_length = 0;
            bool path_found = false;
            float time = -1; 


            
            nlohmann::json out;
            out["id"] = event["id"];

            // Dijkstra
            dijkstra(map, start, goal, nodes_explored, path_length, path_found, time);
            out["dijkstra"]["path_found"] = path_found;
            out["dijkstra"]["path_length"] = path_length;
            out["dijkstra"]["nodes_explored"] = nodes_explored;
            out["dijkstra"]["time_ms"] = time;

            // Reset
            nodes_explored = 0;
            path_length = 0;
            path_found = false;
            time = -1;


            // A* Euclidean
            astar_euclidean(map, start, goal, nodes_explored, path_length, path_found, time);
            out["astar_euclidean"]["path_found"] = path_found;
            out["astar_euclidean"]["path_length"] = path_length;
            out["astar_euclidean"]["nodes_explored"] = nodes_explored;
            
            out["astar_euclidean"]["time_ms"] = time;

            // Reset
            nodes_explored = 0;
            path_length = 0;
            path_found = false;
            time = -1;

            // A* Manhattan
            astar_manhattan(map, start, goal, nodes_explored, path_length, path_found, time);
            out["astar_manhattan"]["path_found"] = path_found;
            out["astar_manhattan"]["path_length"] = path_length;
            out["astar_manhattan"]["nodes_explored"] = nodes_explored;
            
            out["astar_manhattan"]["time_ms"] = time;

            
            output_json["results"].push_back(out);

            
    } 

    else if(type == "tsp") {
        nlohmann::json out;
        out["id"] = event["id"];


        int optimal_cost = 1e9;
        vector<int> nodes = event["nodes"];
        vector<int> tour;
        TSPBruteForce(map, optimal_cost, tour, nodes);
        out["brute_force"]["optimal_cost"] = optimal_cost;
        out["brute_force"]["tour"] = tour;

        int optimal_cost2 = 1e9;
        vector<int> nodes2 = event["nodes"];
        vector<int> tour2;
        TSPHeldKarp(map, optimal_cost2, tour2, nodes2);
        out["held_karp"]["optimal_cost"] = optimal_cost;
        out["held_karp"]["tour"] = tour;

        
        output_json["results"].push_back(out);
    }




}

    ofstream outfile(output_file);

    if (!outfile.is_open()) {
        cerr << "Error: Could not open " << output_file << '\n';
        return 1;
    }

    outfile << output_json.dump(4);

    return 0;
 }