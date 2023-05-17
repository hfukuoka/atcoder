#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define ll long long
#define repll(i, n) for (ll i = 0; i < n; ++i)
#define rep_upll(i, a, n) for (ll i = a; i < n; ++i)
#define rep_downll(i, a, n) for (ll i = a; i >= n; --i)
#define Pll pair<ll, ll>
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep_up(i, a, n) for (int i = a; i < n; ++i)
#define rep_down(i, a, n) for (int i = a; i >= n; --i)
#define P pair<int, int>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define vvvi vector<vector<vector<int>>>
#define vvi vector<vector<int>>
#define vi vector<int>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>
#define pqi priority_queue<int>
#define pqgi priority_queue<int, vector<int>, greater<int>>
#define pb push_back
#define eb emplace_back
const ll INF = (1ll << 60);
const double pi = 3.14159265358979323846;

template<typename T>
void printv(vector<T> &v){
    for(auto e:v)cout << e << " ";
    cout << "\n";
}

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
template<typename Tx, typename Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
ll modpow(ll a, ll n, ll mod){
    if(n == 0) return 1;
    a %= mod;
    if(n % 2) return modpow(a, n-1, mod) * a % mod;
    else return modpow(a*a%mod, n/2, mod);
}
long long modDiv(long long a, long long b, long long m) {
	// Get the value of a/b
	return (a * modpow(b, m - 2, m)) % m;
}

struct Edge {
    long long to;
    long long cost;
};
using Graph = vector<vector<Edge>>;

/* dijkstra(G,s,dis)
    入力：グラフ G, 開始点 s, 距離を格納する dis
    計算量：O(|E|log|V|)
    副作用：dis が書き換えられる
*/
void dijkstra(const Graph &G, int s, vector<long long> &dis) {
    int N = G.size();
    dis.assign(N, INF);
    priority_queue<Pll, vector<Pll>, greater<Pll>> pq;  // 「仮の最短距離, 頂点」が小さい順に並ぶ
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty()) {
        Pll p = pq.top();
        pq.pop();
        int v = p.second;
        if (dis[v] < p.first) {  // 最短距離で無ければ無視
            continue;
        }
        for (auto &e : G[v]) {
            if (dis[e.to] > dis[v] + e.cost) {  // 最短距離候補なら priority_queue に追加
                dis[e.to] = dis[v] + e.cost;
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> c(n), r(n);
    rep(i, n){
        cin >> c[i] >> r[i];
    }
    vector<vector<int>> to(n);
    rep(i, k){
        int a, b;
        cin >> a >> b;
        a--, b--;
        to[a].push_back(b);
        to[b].push_back(a);
    }
    Graph g(n);
    rep(i, n){
        vector<int> d(n, -1);
        d[i] = 0;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int v = q.front(); q.pop();
            for(auto nv:to[v]){
                if(d[nv]!=-1)continue;
                d[nv] = d[v] + 1;
                q.push(nv);
            }
        }
        rep(j, n){
            if(d[j]<=r[i])g[i].push_back({j, c[i]});
        }
    }
    vector<ll> dist(n, INF);
    dist[0] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        auto [cd, v] = pq.top(); pq.pop();
        if(dist[v] < cd)continue;
        for(auto &e:g[v]){
            if(chmin(dist[e.to], dist[v]+e.cost))pq.push({dist[e.to], e.to});
        }
    }
    cout << dist[n-1] << endl;
    return 0;
}