#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include<queue>
#include "json.hpp"

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

    int n;
    vector<int> no;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> dist;
    const int INF = 1e9;


    
    Graph(nlohmann::json& graph) {
        if (graph.contains("grid_size")) {
            inp = graph;
            get_size();
            parse(); 
        }

        else if (graph.contains("nodes")) {
            inp = graph;
            get_nodes();
            make_adj();
            make_dist();
        }

    }

    void get_nodes(){
        
        for(const auto& node: inp["nodes"]){
            no.push_back(node); 
        }

        n = no.size();
        
    }

    void make_adj(){
        adj.resize(n);

        for(const auto& edge:inp["edges"]){
            adj[edge["u"]].push_back({edge["v"], edge["w"]});
            adj[edge["v"]].push_back({edge["u"], edge["w"]});
        }
    }

    void make_dist(){
        dist.assign(n, vector<int>(n, INF)); 
        
        for(int i =0; i<n; i++){
            dijj(i);
        }
    }

    void dijj(int i){

        priority_queue<pair<int, int>> frontier;
        dist[i][i] = 0;
        frontier.push({0, i});

        while(!frontier.empty()){
            int d = -frontier.top().first; 
            int c = frontier.top().second;
            frontier.pop();

            if (d != dist[i][c]) continue;

            for(const auto& nbr : adj[c]){
                if(dist[i][nbr.first] > nbr.second + dist[i][c]) {
                    dist[i][nbr.first] = nbr.second + dist[i][c];
                    frontier.push({-dist[i][nbr.first], nbr.first});
                }

            }
 
        }
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


#endif