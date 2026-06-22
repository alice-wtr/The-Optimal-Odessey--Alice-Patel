#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        adj[a].push_back({b, c});
    }

    const long long INF = 1e18;
    const long long MOD = 1000000007;

    vector<long long> dist(n, INF);
    vector<long long> ways(n, 0);
    vector<int> mn(n, INT_MAX);
    vector<int> mx(n, INT_MIN);

    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    dist[0] = 0;
    ways[0] = 1;
    mn[0] = 0;
    mx[0] = 0;

    pq.push({0, 0});

    while(!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d != dist[u]) {
            continue;
        }

        int sz = adj[u].size();

        for(int i = 0; i < sz; i++) {
            int v = adj[u][i].first;
            long long w = adj[u][i].second;

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                mn[v] = mn[u] + 1;
                mx[v] = mx[u] + 1;

                pq.push({dist[v], v});
            }
            else if(dist[v] == dist[u] + w) {
                ways[v] += ways[u];
                ways[v] %= MOD;

                mn[v] = min(mn[v], mn[u] + 1);
                mx[v] = max(mx[v], mx[u] + 1);
            }
        }
    }

    cout << dist[n-1] << " "
         << ways[n-1] << " "
         << mn[n-1] << " "
         << mx[n-1];
}