#include<bits/stdc++.h>
using namespace std;

void dfs(int a, vector<bool>& seen, vector<int>& parent, vector<int>& level, vector<vector<int>>& adj) {

        int l = adj[a].size();

        for(int i =0; i<l; i++) {
                if(seen[adj[a][i]] == false) {
                        seen[adj[a][i]] = true;
                        parent[adj[a][i]] = a;
                        level[adj[a][i]] = level[a] + 1;
                        dfs(adj[a][i], seen, parent, level, adj);
                }

                else {
                        if(level[a] - level[adj[a][i]] > 1) {
                                cout << level[a] - level[adj[a][i]] + 2 << endl;

                                                        cout << adj[a][i] + 1   << " " << a+1 << " ";
                                                       int t = parent[a];
                                                        while(t != adj[a][i]) {
                                                                cout << t +1<< " ";
                                                                t = parent[t];
                                                        }
                                                cout << t+1 << " ";
                                                exit(0); }
                }
        }
}


int main() {

        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n, vector<int>(0));

        for(int i=0; i<m; i++) {
                int x, y;
                cin >> x >> y;
                x--; y--;

                adj[x].push_back(y);
                adj[y].push_back(x);

        }

        vector<int> level(n, -1);
        vector<int> parent(n, -1);
        vector<bool> seen(n);

        for(int i =0; i<n; i++) {
                if(!seen[i]) {
                        seen[i] = true;
                        level[i] = 0;
                        dfs(i, seen, parent, level, adj);
                }
        }

        cout << "IMPOSSIBLE" << endl;
}