#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    
    vector<vector<pair<int, long long>>> adj(n, vector<pair<int, long long>>(0));

    for(int i=0; i<m; i++) {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        x--;
        y--;

        adj[x].push_back({y, z}); 
        
    }
    //first is with discount, second without
    vector<pair<long long, long long>> dist(n);

    for(int i=0; i<n; i++) {
        dist[i].first = numeric_limits<long long>::max();
        dist[i].second = numeric_limits<long long>::max();
    }

    //pq has {-distance with discount, -distance without discount}, node
    priority_queue<pair<pair<long long, long long>, int>> pq;
    vector<bool> processed(n);

    pq.push({{0,0}, 0});
    dist[0] = {0,0};

    while(pq.size() != 0) {
        long long wt = pq.top().first.second;
        long long wtd = pq.top().first.first;
        int node = pq.top().second;
        pq.pop();

        if(processed[node]) continue;

        processed[node] = true;

        int l = adj[node].size(); 
        for(int i=0; i<l; i++) {

            pair<int, long long> nbr = adj[node][i];
            
            //if path is not discounted
            if(dist[nbr.first].first > dist[node].first + nbr.second) {
                dist[nbr.first].first = dist[node].first + nbr.second;
                dist[nbr.first].second = dist[node].second + nbr.second;
                pq.push({{-dist[nbr.first].first, -dist[nbr.first].second}, nbr.first}); 
            }
            // if path is discounted
            if(dist[nbr.first].first > dist[node].second + nbr.second/2) {
                dist[nbr.first].first = dist[node].second + nbr.second/2;
                dist[nbr.first].second = dist[node].second + nbr.second;
                pq.push({{-dist[nbr.first].first, -dist[nbr.first].second}, nbr.first});
            }

        }
    }

    
    

    cout << dist[n-1].first;
}