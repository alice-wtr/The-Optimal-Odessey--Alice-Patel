#include<bits/stdc++.h>
using namespace std;

void dfs(int a, vector<bool>& seen, vector<int>& parent, vector<int>& level, vector<vector<int>>& adj, vector<bool>& removed) {

        int l = adj[a].size();

        for(int i =0; i<l; i++) {
                if(seen[adj[a][i]] == false && !removed[adj[a][i]]) {
                        seen[adj[a][i]] = true;
                        parent[adj[a][i]] = a;
                        level[adj[a][i]] = level[a] + 1;
                        dfs(adj[a][i], seen, parent, level, adj, removed);
                }

                else if (seen[adj[a][i]] && !removed[adj[a][i]]) {
                        if(level[a] - level[adj[a][i]] > 0) {
                                //cout << "HII SO I GOT SELECTED" << endl << a << " with the level of " << level[a] << " and " << adj[a][i] << " with the level " << level[adj[a][i]];
                                cout << level[a] - level[adj[a][i]] + 2 << endl;

                                                       vector<int> path(0);
                                                       path.push_back(adj[a][i]);
                                                       path.push_back(a);

                                                       int t = parent[a];
                                                        while(t != adj[a][i]) {
                                                                path.push_back(t);
                                                                t = parent[t];
                                                        }
                                                path.push_back(t);

                                                reverse(path.begin(), path.end());

                                                int z = path.size();

                                                for(int k = 0; k<z; k++) {
                                                        cout << path[k] + 1 << " ";
        }       }                               exit(0); }

                
        }
}



int main() {

        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n, vector<int>(0));
        vector<vector<int>> jda(n, vector<int>(0));
        vector<int> outdeg(n); 

        for(int i=0; i<m; i++) {
                int x, y;
                cin >> x >> y;
                x--; y--;

                adj[x].push_back(y);
                jda[y].push_back(x);
                outdeg[x]++;


        }

        queue<int> nulls;
        vector<int> v(0);

        for(int i=0; i<n; i++) {
                if(adj[i].size() == 0) {
                        nulls.push(i);
                }

                v.push_back(i);
        }

        vector<bool> removed(n);

        

        while(nulls.size() != 0) {

                int c = nulls.front();
                nulls.pop();
                removed[c] = true;

                 

                int l = jda[c].size();
                for(int i=0; i<l; i++) {

                        //p is the pre-element of c 
                        int p = jda[c][i];
                        outdeg[p]--; 

                        

                        if(outdeg[p] == 0) {nulls.push(p); }
                              
                }
                
        }

        

        vector<int> level(n, -1);
        vector<int> parent(n, -1);
        vector<bool> seen(n);

        

        for(int i =0; i<n; i++) {
                if(!seen[i] && !removed[i]) {
                        seen[i] = true;
                        level[i] = 0;
                        dfs(i, seen, parent, level, adj, removed);
                }
        }

        cout << "IMPOSSIBLE";

}