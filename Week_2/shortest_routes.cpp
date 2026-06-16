#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>(0));

    for(int i=0; i<m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;

        adj[x].push_back({y, z}); 
        
    }

    vector<long long> dist(n);

    for(int i=0; i<n; i++) {
        dist[i] = numeric_limits<long long>::max();
    }

    priority_queue<pair<long long, int>> pq;
    vector<bool> processed(n);

    pq.push({0, 0});
    dist[0] = 0;

    while(pq.size() != 0) {
        long long wt = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(processed[node]) continue;

        processed[node] = true;

        int l = adj[node].size(); 
        for(int i=0; i<l; i++) {
            
            if(dist[adj[node][i].first] > dist[node] + adj[node][i].second) {
                dist[adj[node][i].first] = dist[node] + adj[node][i].second;
                pq.push({-dist[adj[node][i].first], adj[node][i].first}); 
            }

        }
    }

    for(int i=0; i<n; i++) {
        cout << dist[i] << " ";
    }
}