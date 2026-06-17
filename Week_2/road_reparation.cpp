#include<bits/stdc++.h>
using namespace std;

int top(int v, vector<int>& head) {
    int i = v;
    while(head[i] != i) {i = head[i];}
    return i;
}

int same(int v1, int v2, vector<int>& head) {
    return (top(v1, head) == top(v2, head));
}

int main() {

    int n, m;
    cin >> n >> m;

    priority_queue<pair<long long, pair<int, int>>> edges;

    for(int i = 0; i<m; i++) {
        int x,y;
        long long z;
        cin >> x >> y >> z;
        x--; y--; 

        edges.push({-z, {x,y}}); 

    }

    long long apple = 0;

    vector<int> head(n);
    vector<int> size(n);

    for(int i = 0; i<n; i++) {
        head[i] = i;
        size[i] = 1;
    }

    while(edges.size() != 0) {
        int v1 = edges.top().second.first;
        int v2 = edges.top().second.second;
        int wt = (-1)*edges.top().first;

        edges.pop();

        if(!same(v1, v2, head)) {
            if(size[top(v1, head)] > size[top(v2, head)]){
                size[top(v1, head)] = size[top(v1, head)] + size[top(v2, head)];
                head[top(v2, head)] = top(v1, head);
                
                if(size[top(v1, head)] == n) {cout << apple + wt; return 0;} }
                
            
            else {
                size[top(v2, head)] = size[top(v1, head)] + size[top(v2, head)];
                head[top(v1, head)] = top(v2, head);
                
                if(size[top(v2, head)] == n) {cout << apple + wt; return 0;}
                
            }

            apple = apple + wt;
        }    

    }


    cout << "IMPOSSIBLE";
} 


