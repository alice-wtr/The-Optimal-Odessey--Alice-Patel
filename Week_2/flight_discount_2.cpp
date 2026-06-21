#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--;
        b--;

        adj[a].push_back({b, c});
    }

    const long long INF = 1e18;

    // dist[node][0] = discount not used yet
    // dist[node][1] = discount already used
    vector<vector<long long>> dist(n, vector<long long>(2, INF));
    vector<vector<bool>> processed(n, vector<bool>(2, false));

    // {-distance, node, used}
    priority_queue<tuple<long long, int, int>> pq;

    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {

        auto [negd, u, used] = pq.top();
        pq.pop();

        long long d = -negd;

        if (processed[u][used]) continue;
        processed[u][used] = true;

        for (auto [v, w] : adj[u]) {

            if (!used) {

                // Don't use discount
                if (dist[v][0] > d + w) {
                    dist[v][0] = d + w;
                    pq.push({-dist[v][0], v, 0});
                }

                // Use discount here
                if (dist[v][1] > d + w / 2) {
                    dist[v][1] = d + w / 2;
                    pq.push({-dist[v][1], v, 1});
                }

            } else {

                // Discount already used
                if (dist[v][1] > d + w) {
                    dist[v][1] = d + w;
                    pq.push({-dist[v][1], v, 1});
                }
            }
        }
    }

    cout << dist[n - 1][1] << '\n';
}