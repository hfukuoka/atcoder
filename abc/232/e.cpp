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

using mint = modint998244353;

int main(){
    ll h, w, k;
    cin >> h >> w >> k;
    ll si, sj, gi, gj;
    cin >> si >> sj >> gi >> gj;
    si--, sj--, gi--, gj--;
    vector<mint> dp(4, 0);
    if(si==gi && sj==gj)dp[0]=1;
    if(si==gi && sj!=gj)dp[1]=1;
    if(si!=gi && sj==gj)dp[2]=1;
    if(si!=gi && sj!=gj)dp[3]=1;
    rep(i, k){
        vector<mint> ndp(4, 0);
        ndp[3] += dp[3]*(h+w-4);
        ndp[1] += dp[3];
        ndp[2] += dp[3];
        ndp[1] += dp[0]*(w-1);
        ndp[2] += dp[0]*(h-1);
        ndp[0] += dp[1];
        ndp[1] += dp[1]*(w-2);
        ndp[3] += dp[1]*(h-1);
        ndp[0] += dp[2];
        ndp[2] += dp[2]*(h-2);
        ndp[3] += dp[2]*(w-1);
        swap(ndp, dp);
    }
    cout << dp[0].val() << endl;
    return 0;
}