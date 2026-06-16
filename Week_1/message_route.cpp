#include <bits/stdc++.h>
using namespace std;


int main() {

        int n, m;
        cin >> n >> m;

        vector<vector <int>> adj(n, vector<int>(0));

        for(int i = 0; i<m; i++) {
                int x, y;
                cin >> x;
                cin >> y;
                x--; y--;
                adj[x].push_back(y);
                adj[y].push_back(x);

        }

//      cout << "I AM HERE" << endl; 

        queue<int> frontier;
        vector<char> nodes(n, 'u');
        vector<int> parent(n);

        parent[0] = -1;



   //     cout << "HERE IS I" << endl;


        int end = -1;

        frontier.push(0);
        nodes[0] = 's';
        while(frontier.size() != 0) {
                int x = frontier.front();
                frontier.pop();

                int l = adj[x].size();


                for(int i=0; i<l; i++) {
                        if(adj[x][i] == n-1 && nodes[adj[x][i]] != 's') {
                                nodes[adj[x][i]] = 's';
                                end = adj[x][i];
                                parent[adj[x][i]] = x;
                       break;   }

                        if(nodes[adj[x][i]] == 'u') {
                        nodes[adj[x][i]] = 's';
                        frontier.push(adj[x][i]);
                        parent[adj[x][i]] = x;
                        }
                }
        }
        //cout << "IT IS ME." << endl; 
        vector<int> path(0);

        if(end == -1) {cout << "IMPOSSIBLE"; return 0;}

        int t = end;

        while(t != -1) {
                path.push_back(t);
                t = parent[t];
        }

        reverse(path.begin(), path.end());

        cout << path.size() << "\n";

        for(int i =0; i<path.size(); i++){
                cout << path[i] + 1 << " ";
        }
}
