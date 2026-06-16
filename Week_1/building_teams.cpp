#include<bits/stdc++.h>
using namespace std;

void process(vector<vector<int>>& adj, vector<int>& taken, int a) {

        int l = adj[a].size();

        for(int i =0; i<l; i++) {
                if(taken[adj[a][i]] == 0) {

                       if(taken[a] == 1) {
                                taken[adj[a][i]] = 2;
                                //cout << "MADE 2 FOR" << adj[a][i] << endl;
                       }
                       else {
                               taken[adj[a][i]] = 1;
                               //cout << "MADE 1 FOR" << adj[a][i] << endl;

                       }

                       process(adj, taken, adj[a][i]);
                }
        }
}


int main() {

        int n, m;

        cin >> n >> m;

        vector<vector<int>> adj(n, vector<int>(0));
        vector<int> taken(n, 0);

        for(int i=0; i<m; i++) {

                int x, y;
                cin >> x >> y;

                x--; y--;

                adj[x].push_back(y);
                adj[y].push_back(x);
        }

        for(int i=0; i<n; i++) {
                if(taken[i] == 0) {
                        taken[i] = 1;
                        //cout << "MADE 1 FOR " << i << "FROM MAIN" << endl;
                        process(adj, taken, i);
                }
        }

        for(int i=0; i<n; i++) {
                int l = adj[i].size();

                for(int j = 0; j<l; j++) {
                        if(taken[i] - taken[adj[i][j]] == 0) {
                        //      cout << taken[i] << " " << i << " " << taken[adj[i][j]] << " " << adj[i][j] <<  endl;
                                cout << "IMPOSSIBLE" << endl;
                                return 0;
                        }
                }
        }

        for(int i=0; i<n; i++) {
                cout << taken[i] << " ";
        }
}