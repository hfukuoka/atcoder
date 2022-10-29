#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define ll long long
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep_up(i, a, n) for (ll i = a; i < n; ++i)
#define rep_down(i, a, n) for (ll i = a; i >= n; --i)
#define P pair<ll, ll>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>

const ll INF = (1ll << 60);
const ll mod = 1000000007;
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
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

using Graph = vector<vector<long long>>;

// 探索
vector<bool> seen, finished;

// サイクル復元のための情報
int pos = -1; // サイクル中に含まれる頂点 pos
stack<int> hist; // 訪問履歴

void dfs(const Graph &G, int v, int p) {
    seen[v] = true;
    hist.push(v);
    for (auto nv : G[v]) {
        if (nv == p) continue; // 逆流を禁止する

        // 完全終了した頂点はスルー
        if (finished[nv]) continue;

        // サイクルを検出
        if (seen[nv] && !finished[nv]) {
            pos = nv;
            return;
        }

        // 再帰的に探索
        dfs(G, nv, v);

        // サイクル検出したならば真っ直ぐに抜けていく
        if (pos != -1) return;
    }
    hist.pop();
    finished[v] = true;
}

// 辺の定義
struct Edge {
    long long u;
    long long v;
    long long cost;
};
bool comp_e(const Edge &e1, const Edge &e2) { return e1.cost < e2.cost; } // 辺を直接比較するための関数
bool comp_p(const pair<Edge, ll> &p1, const pair<Edge, ll> &p2){
    return p1.first.cost < p2.first.cost;
}

int main(){
    ll n, m, q;
    cin >> n >> m >> q;
    vector<Edge> es1(m);
    rep(i,m){
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        Edge e = {a, b, c};
        es1[i] = e;
    }
    vector<pair<Edge, ll>> es2(q);
    rep(i, q){
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        Edge e = {u, v, w};
        es2[i] = {e, i};
    }
    sort(all(es1), comp_e);
    sort(all(es2), comp_p);
    ll l = 0;
    dsu uf(n);
    vll ans(q);
    rep(i, q){
        auto [e, j] = es2[i];
        auto r = lower_bound(all(es1), e, comp_e) - es1.begin();
        if(l==m){
            ans[j] = 0;
            continue;
        }
        rep_up(k, l, r){
            auto [a, b, c] = es1[k];
            if(a==b)continue;
            if(uf.same(a, b)) continue;
            uf.merge(a, b);
        }
        if(uf.same(e.u, e.v))ans[j] = 0;
        else ans[j] = 1;
        l = r;
    }
    for(auto a:ans){
        cout << (a ? "Yes" : "No") << endl;
    }
    return 0;
}