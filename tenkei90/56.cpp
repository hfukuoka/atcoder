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
    ll n, s;
    cin >> n >> s;
    vll a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];
    vvll dp(n+1, vll(s+1, 0));
    dp[0][0] = 1;
    rep(i, n){
        rep(j, s+1){
            if(a[i]+j <= s)chmax(dp[i+1][a[i]+j], dp[i][j]);
            if(b[i]+j <= s)chmax(dp[i+1][b[i]+j], dp[i][j]);
        }
    }
    string ans = "";
    if(dp[n][s] >= 1){
        rep_down(i, n, 1){
            if(s-a[i-1]>=0){
                if(dp[i-1][s-a[i-1]]){
                    ans += 'A';
                    s -= a[i-1];
                }
                else{
                    ans += 'B';
                    s -= b[i-1];
                }
            }else{
                ans += 'B';
                s -= b[i-1];
            }
        }
        reverse(all(ans));
        cout << ans << endl;
    }else{
        cout << "Impossible" << endl;
    }
    return 0;
}