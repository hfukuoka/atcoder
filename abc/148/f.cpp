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

// Lowest Common Ancestor by binary lifting
// https://youtu.be/8uowVvQ_-Mo?t=4306
template<typename T> // T: type of cost
struct LCA {
  int n, root, l;
  vector<vector<int>> to;
  vector<vector<T>> co;
  vector<int> dep;
  vector<T> costs;
  vector<vector<int>> par;
  LCA(int n):n(n),to(n),co(n),dep(n),costs(n) {
    l = 0;
    while ((1<<l) < n) ++l;
    par = vector<vector<int>>(n+1,vector<int>(l,n));
  }
  void addEdge(int a, int b, T c=0) { // (a, b) コストcの無向辺を作成
    to[a].push_back(b); co[a].push_back(c);
    to[b].push_back(a); co[b].push_back(c);
  }
  void dfs(int v, int d=0, T c=0, int p=-1) { // dfsして距離とコストを算出
    if (p != -1) par[v][0] = p;
    dep[v] = d;
    costs[v] = c;
    for (int i = 0; i < to[v].size(); ++i) {
      int u = to[v][i];
      if (u == p) continue;
      dfs(u, d+1, c+co[v][i], v);
    }
  }

  void init(int _root=0) { // _rootを根とする木を構築
    root = _root;
    dfs(root);
    for (int i = 0; i < l-1; ++i) {
      for (int v = 0; v < n; ++v) {
        par[v][i+1] = par[par[v][i]][i];
      }
    }
  }
  // LCA
  int lca(int a, int b) { // lcaを求める
    if (dep[a] > dep[b]) swap(a,b);
    int gap = dep[b]-dep[a];
    for (int i = l-1; i >= 0; --i) {
      int len = 1<<i;
      if (gap >= len) {
        gap -= len;
        b = par[b][i];
      }
    }
    if (a == b) return a;
    for (int i = l-1; i >= 0; --i) {
      int na = par[a][i];
      int nb = par[b][i];
      if (na != nb) a = na, b = nb;
    }
    return par[a][0];
  }
  int length(int a, int b) { // 1辺の長さ1のときの距離
    int c = lca(a,b);
    return dep[a]+dep[b]-dep[c]*2;
  }
  T dist(int a, int b) { // 辺ごとにコストがある場合の距離
    int c = lca(a,b);
    return costs[a]+costs[b]-costs[c]*2;
  }
};

int main(){
    int n, u, v;
    cin >> n >> u >> v;
    u--, v--;
    LCA<int> t(n);
    rep(i, n-1){
        int a, b;
        cin >> a >> b;
        a--, b--;
        t.addEdge(a, b, 1);
    }
    t.init(u);
    int ans = 0;
    rep(leaf, n){
        if(t.to[leaf].size()!=1)continue; // 葉を全探索
        int lc = t.lca(leaf, v);
        int taka = t.dist(lc, u);
        int aoki = t.dist(lc, v);
        int taka2 = t.dist(u, leaf);
        int aoki2 = t.dist(v, leaf);
        // cout << "leaf:" << leaf << " lc:" << lc << " taka:" << taka << " aoki:" << aoki << " taka2:" << taka2 << " aoki2:" << aoki2 << endl;
        if(aoki<=taka)continue; // 高橋くんの方が遠くて葉にたどり着けない場合は無視
        int cnt = taka2 + (aoki2 - taka2 - 1); // 高橋くんが葉にたどりつくまで + 青木くんがその葉で高橋くんと合流するまで
        chmax(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}