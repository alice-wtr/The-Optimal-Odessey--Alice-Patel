#include<bits/stdc++.h>
using namespace std;

int main() {

        int n,m;
        cin >> n >> m;

        vector<vector<char>> maze(n, vector<char>(m));
        vector<vector<char>> action(n, vector<char>(m));
        vector<vector<char>> parent(n, vector<char>(m));
        vector<vector<pair<int, int>>> appa(n, vector<pair<int, int>>(m));
        pair<int, int> goal;
        pair<int, int> start;
        for(int i=0; i<n; i++) {
                for(int j=0; j<m; j++) {
                        cin >> maze[i][j];

                        if(maze[i][j] == 'A') {
                                start = {i,j}; }
                        if(maze[i][j] == 'B') {
                                goal = {i,j}; }

                }
        }


        queue<pair<int, int>> frontier;
        frontier.push(start);

        pair<int, int> end = {-1,-1};
        parent[start.first][start.second] = 'X';
        appa[start.first][start.second] = {-1,-1};

        maze[start.first][start.second] = 'o';

        while(frontier.size() != 0 && end.first == -1) {


                pair<int, int> curr = frontier.front();
                frontier.pop();

                //cout << curr.first << " " << curr.second << endl;
                if(curr == goal) {

                        end = curr;

                }

                if(curr.first>0 && (maze[curr.first-1][curr.second] == '.' || maze[curr.first-1][curr.second] == 'B')) {
                        frontier.push({curr.first-1, curr.second});
                        maze[curr.first-1][curr.second] = 'o';
                        parent[curr.first-1][curr.second] = 'U';
                        appa[curr.first-1][curr.second] = {curr.first, curr.second};    }
                if(curr.second>0 && (maze[curr.first][curr.second-1] == '.' || maze[curr.first][curr.second-1] == 'B')) {
                        frontier.push({curr.first, curr.second-1});
                        maze[curr.first][curr.second-1] = 'o';
                        parent[curr.first][curr.second-1] = 'L';
                        appa[curr.first][curr.second-1] = {curr.first, curr.second}; }
                if(curr.first < n-1 && (maze[curr.first + 1][curr.second]=='.' || maze[curr.first + 1][curr.second]=='B')) {
                        frontier.push({curr.first+1, curr.second});
                        maze[curr.first + 1][curr.second] = 'o';
                        parent[curr.first+1][curr.second] = 'D';
                        appa[curr.first+1][curr.second] = {curr.first, curr.second};}
                if(curr.second < m-1 && (maze[curr.first][curr.second+1] == '.' || maze[curr.first][curr.second+1] == 'B')) {
                        frontier.push({curr.first, curr.second +1});
                        maze[curr.first][curr.second+1] = 'o';
                        parent[curr.first][curr.second+1] = 'R';
                        appa[curr.first][curr.second+1] = {curr.first,curr.second};     }

        }


        //cout << end.first << " " << end.second << endl; 

                if (end.first == -1) {
                        cout << "NO" << endl;
                        return 0;
                }


                vector<char> path(0);
                pair<int, int> t = end;
                while(t != pair<int, int>{-1, -1}) {
                       path.push_back(parent[t.first][t.second]);
                       t = appa[t.first][t.second];
                }

                reverse(path.begin(), path.end());

                int l = path.size();
                cout << "YES\n" << l-1 << endl;

                for(int i = 1; i<l; i++) {
                        cout << path[i];
                }


}