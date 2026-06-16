#include <bits/stdc++.h>
using namespace std;


void process(int a, vector<int>& connected, vector<vector<int>>& adj) {

        int l = adj[a].size();
        for(int i=0; i<l; i++) {
                if(!connected[adj[a][i]]) {
                        connected[adj[a][i]] = true;
                        process(adj[a][i], connected, adj);

                }
        }
}

int main() {

        int n; int m;
        cin >> n >> m;

        vector<int> connected(n);

        vector<vector<int>> adj(n, vector<int>(0));


        vector<pair<int, int>> roads;
        for(int i = 0; i<m; i++) {
                int x, y;
                cin >> x;
                cin >> y;
                x--; y--;
                adj[x].push_back(y);
                adj[y].push_back(x);

        }



        vector<int> joints(0);
        int apple = 0;

        for(int i =0; i<n; i++) {
                if(!connected[i]) {
                        connected[i] = true;
                        joints.push_back(i);
                        apple++;
                        process(i, connected, adj);

                }
        }

        cout << apple-1 << "\n";

        int l = joints.size();
        for(int i=0; i<l-1; i++) {
                cout << joints[i] + 1 << " " << joints[i+1] +1 << "\n";
        }

 }