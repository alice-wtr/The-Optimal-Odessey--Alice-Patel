#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include<algorithm>
#include "../Week_3_4/json.hpp"
#include<chrono>
#include"TSP.h"
using namespace std;


class Graph {

    public:

    nlohmann::json inp;
    int n;
    vector<int> no;
    vector<vector<double>> adj;
    const double INF = numeric_limits<double>::infinity();
    


    
    Graph(nlohmann::json& graph) {
        if (graph.contains("nodes")) {
            inp = graph;
            get_nodes();
            make_adj();
        }

    }

    void get_nodes(){
        
        for(const auto& node: inp["nodes"]){
            no.push_back(node); 
        }

        n = no.size();
        
    }

    

    void make_adj() {
        adj.assign(n, vector<double>(n, INF));

        for (int i = 0; i < n; i++)
            adj[i][i] = 0;

        for (const auto& edge : inp["edges"]) {
            int u = edge["u"];
            int v = edge["v"];
            double w = edge["w"];

            adj[u][v] = w;
            adj[v][u] = w;
        }
    }



};


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
        /*
        if(type == "remove_edge") {
            int edge_id = event["edge_id"];
            bool b = remove_edge(map, edge_id);
            nlohmann::json out;
            out["id"] = event["id"];
            out["done"] = b;
            std::cout << out.dump(4) << std::endl;
            output_json["results"].push_back(out);
        }
        */

        if(type == "tsp") {
            vector<int> nodes = event["nodes"];
            float time_us = -1;
            double cost;
            vector<int> tour = christofides(map.adj, nodes, time_us, cost);
            nlohmann::json out;
            out["id"] = event["id"];
            out["results"]["time_us"] = time_us;
            out["results"]["tour"] = tour;
            out["results"]["cost"] = cost;
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
