#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)
template <typename T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}

struct edge{
    int to;
    int cost;
};

bool comp(const edge &e1, const edge &e2){
    if(e1.cost != e2.cost)return e1.cost < e2.cost;
    else return e1.to < e2.to;
}

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
    rep(i, n)sort(g[i].begin(), g[i].end(), comp);
    rep(v, n){
        if(g[v].size()==0){
            cout << -1 << endl;
            continue;
        }
        int ans = g[v][0].to;
        cout << ans << endl;
    }

    return 0;
}