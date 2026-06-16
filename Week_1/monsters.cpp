#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    vector<string> g(n);
    for(int i = 0; i < n; i++) {
        cin >> g[i];
    }

    vector<vector<int>> mon(n, vector<int>(m, 1e9));
    vector<vector<int>> dis(n, vector<int>(m, 1e9));
    vector<vector<pair<int,int>>> par(n, vector<pair<int,int>>(m, {-1, -1}));

    queue<pair<int,int>> q;

    // multi-source BFS for monsters
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'M') {
                q.push({i, j});
                mon[i][j] = 0;
            }
        }
    }

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if(g[nx][ny] != '#' && mon[nx][ny] > mon[x][y] + 1) {
                    mon[nx][ny] = mon[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    // BFS for player
    queue<pair<int,int>> pq;
    pair<int,int> start;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'A') {
                pq.push({i, j});
                dis[i][j] = 0;
                start = {i, j};
            }
        }
    }

    string ans = "";
    bool ok = false;
    pair<int,int> end;

    while(!pq.empty()) {
        auto [x, y] = pq.front();
        pq.pop();

        // check escape
        if(x == 0 || x == n-1 || y == 0 || y == m-1) {
            ok = true;
            end = {x, y};
            break;
        }

        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if(g[nx][ny] != '#' &&
                   dis[nx][ny] == 1e9 &&
                   dis[x][y] + 1 < mon[nx][ny]) {

                    dis[nx][ny] = dis[x][y] + 1;
                    par[nx][ny] = {x, y};
                    pq.push({nx, ny});
                }
            }
        }
    }

    if(!ok) {
        cout << "NO\n";
        return 0;
    }

    // reconstruct path
    cout << "YES\n";

    string path = "";
    pair<int,int> cur = end;

    while(cur != start) {
        auto p = par[cur.first][cur.second];

        if(p.first == cur.first + 1) path += 'U';
        else if(p.first == cur.first - 1) path += 'D';
        else if(p.second == cur.second + 1) path += 'L';
        else path += 'R';

        cur = p;
    }

    cout << path.size() << endl;

    reverse(path.begin(), path.end());
    cout << path << "\n";

    return 0;
}