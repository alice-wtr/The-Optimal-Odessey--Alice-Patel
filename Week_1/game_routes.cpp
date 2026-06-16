#include <bits/stdc++.h>
#include<cmath>
using namespace std;

long long paths(int a, vector<vector<int>>& adj, vector<vector<int>>& jda, vector<long long>& path, long long num) {

        
        if(path[a] >= 0) {return path[a];}

        long long t = 0;
        int l = jda[a].size(); 
        for(int i=0; i<l; i++) {
                t = (t + paths(jda[a][i], adj, jda, path, num))%num;
        }
        path[a] = t;
        return t;

}


int main() {

        int n, m;
        cin >> n >> m;
        const long long num = 1000000007;

        vector<vector <int>> adj(n, vector<int>(0));
        vector<vector <int>> jda(n, vector<int>(0));
        vector<long long> path(n, -1); 
        path[0] = 1;

        for(int i = 0; i<m; i++) {
                int x, y;
                cin >> x;
                cin >> y;
                x--; y--;
                adj[x].push_back(y);
                jda[y].push_back(x);         
        }

        long long s = -1;
        for(int i = 0; i<n; i++) {
                s = paths(i, adj, jda, path, num);
        }
        cout << s;

}