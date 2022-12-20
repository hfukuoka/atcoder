#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;
vector<bool> seen;

void dfs(const Graph &g, int v, vector<int> &prev){
    seen[v] = true;
    for(auto nv:g[v]){
        if(seen[nv])continue;
        prev[nv] = v;
        dfs(g, nv, prev);
    }
    return;
}

int main(){
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph g(n);
    rep(i, m){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    seen.assign(n, false);
    vector<int> prev(n, -1);
    dfs(g, s, prev);

    vector<int> path;
    int now = t;
    while(now!=-1){
        path.push_back(now);
        now = prev[now];
    }
    reverse(path.begin(), path.end());
    int sz = path.size();
    cout << sz << endl;;
    rep(i, sz){
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;
}
