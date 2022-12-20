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

int main(){
    int n;
    cin >> n;
    vvll a(n, vll(n));
    rep(i, n)rep(j, n)cin >> a[i][j];
    vector dp1(n, vector<map<ll, ll>>(n));
    vector dp2(n, vector<map<ll, ll>>(n)); // (n-1, n-1)までで0になるには(i, j)までの和がなんだったら良いか
    dp1[0][0][a[0][0]] = 1;
    rep(i, n){
        rep(j, n){
            if(i+j>=n-1)break;
            for(auto [k, d]:dp1[i][j]){
                if(i+1<n)dp1[i+1][j][k^a[i+1][j]] += dp1[i][j][k];
                if(j+1<n)dp1[i][j+1][k^a[i][j+1]] += dp1[i][j][k];
            }
        }
    }
    dp2[n-1][n-1][0] = 1;
    ll ans = 0;
    rep_down(i, n-1, 0){
        rep_down(j, n-1, 0){
            if(i+j<n){
                for(auto [k, d]:dp2[i][j]){
                    ans += dp1[i][j][k] * dp2[i][j][k];
                }
                break;
            }
            for(auto [k, d]:dp2[i][j]){
                if(i-1>=0) dp2[i-1][j][k^a[i][j]] += dp2[i][j][k];
                if(j-1>=0) dp2[i][j-1][k^a[i][j]] += dp2[i][j][k];
            }
        }
    }
    cout << ans << endl;
    return 0;
}