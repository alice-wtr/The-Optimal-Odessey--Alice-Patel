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



using namespace std;




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

            
    } }

    ofstream outfile(output_file);

    if (!outfile.is_open()) {
        cerr << "Error: Could not open " << output_file << '\n';
        return 1;
    }

    outfile << output_json.dump(4);

    return 0;
 }