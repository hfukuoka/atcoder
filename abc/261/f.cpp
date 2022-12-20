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

long long modDiv(long long a, long long b, long long m) {
	// Get the value of a/b
	return (a * modpow(b, m - 2, m)) % m;
}

long long modSum1toX(long long X) {
	// Calculate 1 + 2 + ... + X mod 1000000007
	long long v1 = X % mod;
	long long v2 = (X + 1) % mod;
	long long v = v1 * v2 % mod;
	return modDiv(v, 2, mod);
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
    vll c(n), x(n);
    vvll a(n);
    rep(i, n){
        cin >> c[i];
        c[i]--;
    }
    rep(i, n){
        cin >> x[i];
        x[i]--;
    }
    rep(i, n){
        a[c[i]].push_back(x[i]);
    }
    rep(i, n){
        vll b = a[i];
        sort(all(b));
        b.erase(unique(all(b)), b.end());
        rep(j, (int)a[i].size()){
            a[i][j] = lower_bound(all(b), a[i][j]) - b.begin();
        }
    }
    fenwick_tree<ll> bt(n);
    ll inva=0, invb=0; // inva: xの転倒数, invb: 同じ色同士だけ抽出した場合の転倒数の合計
    rep(i, n){
        bt.add(x[i], 1LL);
        inva += bt.sum(x[i]+1LL, n);
    }
    rep(k, n){
        int m = a[k].size();
        int mx = 0;
        rep(i, m)chmax(mx, (int)a[k][i]);
        fenwick_tree<ll> t(mx+1);
        rep(i, m){
            t.add(a[k][i], 1LL);
            invb += t.sum(a[k][i]+1, mx+1);
        }
    }
    ll ans = inva-invb;
    cout << ans << endl;
    return 0;
}