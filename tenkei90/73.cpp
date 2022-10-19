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

ll n;
char c[1<<18];
long long dp[1<<18][3];

void dfs(const Graph &G, int v, int p) {
    ll val1=1, val2=1;
    for (auto nv : G[v]) {
        if(nv == p) continue;
        dfs(G, nv, v);
        if(c[v]=='a'){
            val1 *= (dp[nv][0] + dp[nv][2]);
            val2 *= (dp[nv][0] + dp[nv][1] + 2LL*dp[nv][2]);
        }
        if(c[v]=='b'){
            val1 *= (dp[nv][1] + dp[nv][2]);
            val2 *= (dp[nv][0] + dp[nv][1] + 2LL*dp[nv][2]);
        }
        val1 %= mod;
        val2 %= mod;
    }
    if(c[v] == 'a'){
        dp[v][0] = val1;
        dp[v][2] = (val2-val1+mod) % mod;
    }
    if(c[v] == 'b'){
        dp[v][1] = val1;
        dp[v][2] = (val2-val1+mod) % mod;
    }
}

int main(){
    cin >> n;
    Graph G(n);
    rep(i, n)cin >> c[i];
    rep(i, n-1){
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(G, 0, -1);
    cout << dp[0][2] << endl;;
    return 0;
}