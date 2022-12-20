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

struct Edge {
    long long from;
    long long to;
    long long cost;
};
using Edges = vector<Edge>;
const int INF = 1e9;

/* bellman_ford(Es,s,t,dis)
    入力: 全ての辺Es, 頂点数V, 開始点 s, 最短経路を記録するdis
    出力: 負の閉路が存在するなら ture
    計算量：O(|E||V|)
    副作用：dis が書き換えられる
*/
bool bellman_ford(const Edges &Es, int V, int s, vector<long long> &dis) {
    dis.assign(V, 1e9);
    dis[s] = 0;
    int cnt = 0;
    while (cnt < V) {
        bool end = true;
        for (auto e : Es) {
            if (dis[e.from] != INF && dis[e.from] + e.cost < dis[e.to]) {
                dis[e.to] = dis[e.from] + e.cost;
                end = false;
            }
        }
        if (end) break;
        cnt++;
    }
    return (cnt == V);
}

int main(){
    int n, m;
    cin >> n >> m;
    Edges es(m);
    rep(i, m){
        int a, b, w;
        cin >> a >> b >> w;
        es[i] = {a, b, w};
    }
    vector<ll> dis(n);
    dis.assign(n, INF);
    dis[0] = 0;
    int cnt = 0;
    while(cnt<n){
        bool end = true;
        for(auto e:es){
            auto [v, nv, c] = e;
            if(dis[v]!=INF)if(chmin(dis[nv], dis[v]+c))end=false;
        }
        if(end)break;
        cnt++;
    }
    if(dis[n-1]==INF){
        cout << "impossible" << endl;
    }else if(cnt==n){
        cout << "-inf" << endl;
    }else{
        cout << dis[n-1] << endl;
    }
    return 0;
}