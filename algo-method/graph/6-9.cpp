#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;
vector<bool> match;

int ans = 0;

void dfs(const Graph &g, int v, int p){
    bool f = false;
    for(auto nv:g[v]){
        if(nv==p)continue;
        dfs(g, nv, v);
    }
    if(p==-1)return;
    if(match[p]==false && match[v]==false){
        match[v] = match[p] = true;
        ans++;
    }
    return;
}

int main(){
    int n;
    cin >> n;
    Graph g(n);
    rep(i, n-1){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    match.assign(n, false);
    dfs(g, 0, -1);
    cout << ans << endl;
    return 0;
}