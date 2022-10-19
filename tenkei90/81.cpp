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

long long v[5010][5010], s[5010][5010];

int main(){
    ll n, k;
    cin >> n >> k;
    // ll m = 0;
    rep(i, n){
        ll a, b;
        cin >> a >> b;
        v[a][b]++;
        // chmax(m, a);
        // chmax(m, b);
    }
    for(ll i=1; i<=5000; ++i){
        for(ll j=1; j<=5000; ++j){
            s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+v[i][j];
        }
    }
    ll ans = 1;
    for(ll i=1; i+k<=5000; ++i){
        for(ll j=1; j+k<=5000; ++j){
            ll cur = s[i+k][j+k]+s[i-1][j-1]-s[i+k][j-1]-s[i-1][j+k];
            chmax(ans, cur);
        }
    }
    cout << ans << endl;
    // rep(i, m+1){
    //     rep(j, m+1){
    //         cout << v[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}