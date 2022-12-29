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


void dijkstra(const Graph &G, int s, vector<long long> &dis) {
    int V = G.size();
    dis.assign(V, INF);
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
    int N, M, MX, V;
    ll S;
    cin >> N >> M >> S;
    MX = M*50; // 使う硬貨の総数は最大でもM*50
    if(S>MX)S = MX;
    ll W = 1+MX;
    V = N*W; // 最大50*100*50
    Graph G(V);
    rep(i, M){
        ll u, v, a, b;
        cin >> u >> v >> a >> b;
        u--, v--;
        rep_down(c, W-1, 0){
            ll nc = c-a;
            if(nc<0)break;
            ll x = u*W + c;
            ll y = v*W + nc;
            G[x].push_back({y, b});
            x = v*W + c;
            y = u*W + nc;
            G[x].push_back({y, b});
        }
    }
    rep(i, N){
        ll c, d;
        cin >> c >> d;
        rep(j, W){
            ll nj = j+c;
            if(nj>=W)nj = W-1;
            ll x = i*W + j;
            ll y = i*W + nj;
            G[x].push_back({y, d});
        }
    }
    vll dis(V, INF);
    dis[S] = 0;
    dijkstra(G, S, dis);
    vll ans(N, INF);
    rep(i, N){
        rep(j, W){
            int v = i*W + j;
            chmin(ans[i], dis[v]);
        }
    }
    rep_up(i, 1, N){
        cout << ans[i] << '\n';
    }
    return 0;
}