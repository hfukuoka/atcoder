#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

struct edge{
    int to;
    int cost;
};

using Graph = vector<vector<edge>>;
const int INF = 1<<30;

int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n);
    rep(i, m){
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
    }
    vector<int> dist(n, INF);
    dist[0] = 0;
    rep(v, n){
        for(auto [nv, c]:g[v]){
            if(dist[v]!=INF)dist[nv] = min(dist[nv], dist[v]+c);
        }
    }
    int ans;
    if(dist[n-1]==INF) ans = -1;
    else ans = dist[n-1];
    cout << ans << endl;
    return 0;
}