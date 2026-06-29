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



using namespace std;

class Node {
    public: 

    pair<int, int> parent;
    int so_far;
    int x;
    int y;

    Node(pair<int, int> p, int s, pair<int, int> me) {
        parent = p;
        so_far = s;
        x = me.first;
        y = me.second;
    }

    bool operator<(const Node& other) const {
    return false;
}
};

class Graph {

    public:

    nlohmann::json inp;
    int rows;
    int cols;
    vector<std::vector<char>> gra;

    
    Graph(nlohmann::json& graph) {
        inp = graph;
        get_size();
        parse();

    }
    
    void get_size(){
        rows = inp["grid_size"]["rows"];
        cols = inp["grid_size"]["cols"];
    }


    void parse(){
        gra.assign(rows, vector<char>(cols, ' ')); 
        for(auto t : inp["obstacles"]) {
            int xx = t["x"];
            int yy = t["y"];

            gra[xx][yy] = 'O'; 
        }
    }

    vector<Node> get_neighbors(Node current) {

        vector<Node> nbr;

        if(current.y < rows-1 && gra[current.x][current.y+1] != 'O' ) {
            nbr.push_back({{current.x, current.y}, current.so_far + 1, {current.x, current.y+1}});
        }

        if(current.x < rows-1 && gra[current.x+1][current.y] != 'O' ) {
            nbr.push_back({{current.x, current.y}, current.so_far + 1, {current.x+1, current.y}});
        }

        if(current.y > 0 && gra[current.x][current.y-1] != 'O' ) {
            nbr.push_back({{current.x, current.y}, current.so_far + 1, {current.x, current.y-1}});
        }

        if(current.x > 0 && gra[current.x-1][current.y] != 'O' ) {
            nbr.push_back({{current.x, current.y}, current.so_far + 1, {current.x-1, current.y}});
        }

        return nbr;
        

    }

};

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