#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)
using Graph = vector<vector<int>>;



int main(){
    int n, m;
    cin >> n >> m;
    Graph G(n);
    rep(i, m){
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<int> color(n, -1); // 各点の色を表す (0 or 1)
    queue<int> q;
    rep(s, n){
        if(color[s]!=-1)continue;
        q.push(s);
        color[s] = 0;
        while(!q.empty()){
            int v = q.front(); q.pop();
            int c = color[v];
            int nc = 1-c;
            for(auto nv:G[v]){
                if(color[nv]!=-1){
                    if(color[nv]==c){ // 隣接頂点が同じ色ならダメ
                        cout << "No" << endl;
                        return 0;
                    }
                    continue; // 異なる色ならスキップ
                }
                q.push(nv);
                color[nv] = nc;
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}