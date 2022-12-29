#include <bits/stdc++.h>
using namespace std;

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


template <class F> ll optimize(int low, int high, const F& f) {
    while (high - low > 2) {
        const int m1 = (low + high) / 2;
        const int m2 = m1 + 1;
        if (f(m1) < f(m2)) {
            low = m1;
        } else {
            high = m2;
        }
    }
    return f(low + 1);
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll a = 0, b = 0, ans = -INF;
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        const auto f = [&](const int k) {
            return a + b * k + x * k * (k + 1) / 2;
        };
        if (x > 0) {
            ans = max(ans, f(1));
            ans = max(ans, f(y));
        } else {
            ans = max(ans, optimize(0, y + 1, f));
        }
        a = f(y);
        b += x * y;
    }
    cout << ans << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}