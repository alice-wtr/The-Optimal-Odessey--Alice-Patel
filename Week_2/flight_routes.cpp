#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>(0));

    for(int i=0; i<m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;

        adj[x].push_back({y, z}); 
        
    }

    vector<vector<long long>> dist(n, vector<long long>(k)); 

    for(int i=0; i<n; i++) {
        for(int j = 0; j<k; j++) {
        dist[i][j] = numeric_limits<long long>::max(); } 
    }

    priority_queue<pair<long long, int>> pq;
    vector<int> count(n, 0);

    pq.push({0, 0});
    dist[0][0] = 0;

    while(pq.size() != 0) {
        long long wt = -pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(count[node] >= k) continue;
        if(node == n-1) cout << wt << " ";

        count[node]++;

        int l = adj[node].size(); 
        for(int i=0; i<l; i++) {

            pq.push({-(wt + adj[node][i].second), adj[node][i].first});

        }
    }

    
}