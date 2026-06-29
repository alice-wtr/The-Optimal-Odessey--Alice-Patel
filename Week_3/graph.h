#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
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


#endif