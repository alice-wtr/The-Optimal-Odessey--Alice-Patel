#pragma once
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

const double INF = numeric_limits<double>::infinity();



vector<vector<double>> floyd_warshall(vector<vector<double>>& adj, vector<int>& nodes){
    int n = nodes.size();
    vector<vector<double>> dist(n, vector<double>(n));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = adj[nodes[i]][nodes[j]];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]); 
            }
        }
    }

    return dist;

}


vector<pair<int,int>> prim_mst(vector<vector<double>>& dist){ 
    
    int n = dist.size();

    vector<double> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> inMST(n);

    key[0] = 0;

    for (int cnt = 0; cnt < n; cnt++) {

        double best = INF;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!inMST[i] && key[i] < best) {
                best = key[i];
                u = i;
            }
        }

        if (u == -1) break;      

        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && dist[u][v] < key[v]) {
                key[v] = dist[u][v];
                parent[v] = u;
            }
        }
    }

    vector<pair<int,int>> mst;

    for(int i = 1; i < n; i++) {
        if (parent[i] != -1)
            mst.push_back({parent[i], i});
    }

    return mst;
}


vector<pair<int,int>> perfect_matching(vector<int>& odds, vector<vector<double>>& dist) {

    int n = odds.size();
    vector<bool> matched(n, false);
    vector<pair<int,int>> matching;

    for (int i = 0; i < n; i++) {

        if (matched[i]) continue;

        double best = INF;
        int partner = -1;

        for (int j = i + 1; j < n; j++) {
            if (!matched[j] && dist[i][j] < best) {
                best = dist[i][j];
                partner = j;
            }
        }

        if (partner != -1) {
            matched[i] = true;
            matched[partner] = true;

            
            matching.push_back({odds[i], odds[partner]});
        }
    }

    return matching;
}


vector<int> eulerian_circuit(int m, vector<vector<pair<int,int>>>& adj_list){
    //im assuming m is number of undirected edges

    
    int n = adj_list.size();

    vector<bool> used(m, false);
    vector<int> circuit;
    vector<int> ptr(n, 0);
    stack<int> st;

    st.push(0);               

    while (!st.empty()) {
        int u = st.top();

        // Skip edges already used
        while (ptr[u] < adj_list[u].size() && used[adj_list[u][ptr[u]].second]) {
            ptr[u]++;
        }

        // No unused edges left
        if (ptr[u] == adj_list[u].size()) {
            circuit.push_back(u);
            st.pop();
        }
        else {
            auto [v, id] = adj_list[u][ptr[u]];
            used[id] = true;
            st.push(v);
        }
    }

    reverse(circuit.begin(), circuit.end());
    vector<bool> seen(n);
    vector<int> path(0);

    int l = circuit.size();
    for(int i = 0; i<l; i++) {
        if(seen[i] == false) {
            seen[i] = true;
            path.push_back(i);
        }

    }
    path.push_back(path[0]);
    return path;

}

double tour_cost(const vector<int>& tour, vector<vector<double>>& dist){

    double cost;
    
    int f, s;
    int l = tour.size();

    for(int i = 1; i<l; i++){
        f = tour[i-1];
        s = tour[i];
        cost = cost + dist[s][f];
    }

    return cost;

}


// Steps: Floyd-Warshall -> MST -> odd vertices -> matching -> Eulerian circuit -> shorcutting
vector<int> christofides(vector<vector<double>>& adj,vector<int>& nodes){

    vector<vector<double>> dist = floyd_warshall(adj, nodes);

    vector<pair<int, int>> mst = prim_mst(dist);

    

}
