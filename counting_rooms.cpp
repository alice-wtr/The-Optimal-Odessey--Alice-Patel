#include <bits/stdc++.h>
using namespace std;

void explore(int i, int j, int n, int m,  vector<vector<char>>& maps, vector<vector<bool>>& visited) {

                visited[i][j] = true;
                if(i+1 < n && maps[i+1][j] == '.' && !visited[i+1][j]) {
                        explore(i+1, j, n, m, maps, visited); }
                if(i-1>=0 && maps[i-1][j] == '.' && !visited[i-1][j]) {
                        explore(i-1, j, n, m, maps, visited); }
                if(j+1 < m && maps[i][j+1] == '.' && !visited[i][j+1]) {
                        explore(i, j+1, n, m, maps, visited); }
                if(j-1>=0 && maps[i][j-1] == '.' && !visited[i][j-1]) {
                        explore(i, j-1, n, m, maps, visited); }


}

int main() {
    int n;
    cin >> n;
    int m;
    cin >> m;
        int rooms = 0;
    vector<vector<char>> maps(n, vector<char>(m));

    for(int i = 0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> maps[i][j];
        }
    }
//cout<< "STORED";
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for(int i =0; i<n; i++) {
            for(int j=0; j<m; j++) {
                    if(maps[i][j] == '.' && !visited[i][j]) {
                            rooms++;
                            explore(i, j, n, m,  maps, visited);
                    }
            }
    }


cout << rooms << "\n";

}