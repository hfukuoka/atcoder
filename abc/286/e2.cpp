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
using Graph = vector<vector<int>>;

/* topo_sort(G): グラフG をトポロジカルソート
    返り値: トポロジカルソートされた頂点番号
    計算量: O(|E|+|V|)
 */
void dfs(const Graph &G, int v, vector<bool> &used, vector<int> &ans) {
    used[v] = true;
    for (auto nv : G[v]) {
        if (!used[nv]) {
            dfs(G, nv, used, ans);
        }
    }
    ans.push_back(v);  // 帰りがけにpush_back
}
vector<int> topo_sort(const Graph &G) {  // bfs
    vector<int> ans;
    int n = (int)G.size();
    vector<bool> used(n, false);
    for (int v = 0; v < n; v++) {  // 未探索の頂点ごとにDFS
        if (!used[v]) dfs(G, v, used, ans);
    }
    reverse(ans.begin(), ans.end());  // 逆向きなのでひっくり返す
    return ans;
}

int main(){
    ll n;
    cin >> n;
    vll a(n);
    rep(i, n)cin >> a[i];
    vector<string> s(n);
    rep(i, n)cin >> s[i];
    vvll dist(n, vll(n));
    vvll val(n, vll(n));
    rep(i, n){
        rep(j, n){
            if(i==j){
                dist[i][j] = 0;
                val[i][j] = 0;
                continue;
            }
            if(s[i][j]=='Y'){
                dist[i][j]=1;
                val[i][j] = a[j];
            }else dist[i][j] = INF;
        }
    }
    rep(k, n)rep(i, n)rep(j, n){
        if(chmin(dist[i][j], dist[i][k]+dist[k][j])){
            val[i][j] = val[i][k] + val[k][j];
        }else if(dist[i][j] == dist[i][k]+dist[k][j]){
            chmax(val[i][j], val[i][k]+val[k][j]);
        }
    }
    int q;
    cin >> q;
    rep(qi, q){
        int u, v;
        cin >> u >> v;
        u--, v--;
        if(dist[u][v]>=INF){
            cout << "Impossible" << endl;
            continue;
        }
        cout << dist[u][v] << " " << a[u] + val[u][v] << endl;
    }
    return 0;
}