#include<bits/stdc++.h>
using namespace std;

int top(int v, vector<int>& head) {
    if(head[v] == v) return v;
    
    head[v] = top(head[v], head);
    return head[v];


}


int main() {
    int n, m;
    cin >> n >> m;

    vector<int> head(n);
    vector<int> size(n);
    for(int i = 0; i<n; i++) {
        head[i] = i;
        size[i] = 1;
    }
    
    int comp = n; 
    int s = 1;

    for(int i =0; i<m; i++) {
        int x,y;
        cin >> x >> y;
        x--; y--;

        int tx = top(x, head);
        int ty = top(y, head);

        if(tx != ty) {

            comp--;
            
            
            if(tx > ty) {
                size[tx] = size[tx] + size[ty];
                head[ty] = tx;
                if(size[tx] > s) {s = size[tx]; }
            }
            else {

                size[ty] = size[tx] + size[ty];
                head[tx] = ty;
                if(size[ty] > s) {s = size[ty];}

            }           

        } 

        cout << comp << " " << s << "\n";

    }
}
