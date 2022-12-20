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

int n, m;

int main(){
    cin >> n >> m;
    scc_graph g(n);
    vector<vector<int>> to(n);
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--, b--;
        g.add_edge(a, b);
        to[a].push_back(b);
    }
    auto d = g.scc(); // g[i]: sccしたときのi番目のグループの頂点集合 // グループはトポロジカルじゅんに並ぶ
    int s = d.size(); // sccしたときのグループの数
    vector<int> di(n); // di[i]: 頂点番号iのグループ番号
    rep(i, s) for(int v:d[i]) di[v] = i;
    vector<bool> dp(s);
    for(int i=s-1; i>=0; --i){ // 後ろから見ていくO(n+m)
        dp[i] = d[i].size()!=1; // 自分自身にサイクルがあるならOK
        for(int v:d[i]){ //グループ内の全ての頂点について
            for(int u:to[v]){ // 出てる辺をみる
                if(dp[di[u]]) dp[i]=true; // 行き先がtrueならOK
            }
        }
    }
    int ans = 0;
    rep(i, s)if(dp[i]) ans += d[i].size(); // trueのグループの頂点数を足していく
    cout << ans << endl;
    return 0;
}