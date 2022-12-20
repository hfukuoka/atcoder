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

int n;
vector<vector<int>> g;
vector<bool> is_cycle;
vector<int> deg;
vector<int> root_id;

void dfs(int v, int p){
    root_id[v] = root_id[p];
    for(auto nv:g[v]){
        if(nv!=p) dfs(nv, v);
    }
}

int main(){
    cin >> n;
    g.resize(n);
    is_cycle.assign(n, true);
    deg.assign(n, 0);
    root_id.assign(n, -1);
    rep(i, n){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    queue<int> q;
    rep(i, n){
        if(deg[i]==1)q.push(i);
    }
    while(!q.empty()){
        int v = q.front(); q.pop();
        is_cycle[v]=false;
        for(auto nv:g[v]){
            deg[nv]--;
            if(deg[nv]==1)q.push(nv);
        }
    }
    rep(i, n){
        if(is_cycle[i]){
            root_id[i]=i;
            for(auto to:g[i]){
                if(!is_cycle[to]) dfs(to, i);
            }
        }
    }
    int Q;
    cin >> Q;
    rep(qi, Q){
        int x, y;
        cin >> x >> y;
        x--, y--;
        if(root_id[x]==root_id[y]) cout << "Yes" << '\n';
        else cout << "No" << '\n';
    }
    return 0;
}