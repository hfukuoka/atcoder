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

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) { // 前処理。spf を求める
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) { // nの素因数分解を求める
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};

int main(){
    ll n, q, x;
    cin >> n >> q >> x;
    vll w(n);
    rep(i, n)cin >> w[i];
    vll s(n+1, 0);// s[i]:w[i-1]までの累積和
    rep(i, n){
        s[i+1] = s[i]+w[i];
    }
    vll c(n); //ジャガイモiスタートで何個箱に入れるか
    rep(i, n){
        ll youryo = x+s[i]; // 容量をi-1までのジャガイモ分増やす
        // youryo/s[n]:n個のジャガイモを加えることを何周できるか
        // youryo%s[n]:何周かした後に残ってる容量
        auto r = lower_bound(all(s), youryo%s[n]) - s.begin();
        c[i] = (youryo/s[n])*n + r - i;
        // cout << youryo << " " << r << " " << i << endl;
        // cout << c[i] << endl;
    }
    vll ans(n+1), v(n, -1); // v[i]:i番目スタートは何回目か
    ll id=0, cnt=0; //はじめ、0ジャガイモスタート
    ll m=-1; // 周期
    ll st=-1; //周期スタートの点
    rep(i, n+1){
        if(v[id]!=-1){
            m = cnt-v[id];
            st = v[id];
            break;
        }
        ans[cnt] = c[id];
        v[id] = cnt;
        cnt++;
        id = (id+c[id])%n;
    }
    // rep(i, n)cout << ans[i] << endl;
    if(m==-1){
        while(q){
            q--;
            ll k;
            cin >> k;
            k--;
            cout << ans[k] << endl;
        }
        return 0;
    }
    while(q){
        q--;
        ll k;
        cin >> k;
        k--;
        if(k<st) cout << ans[k] << endl;
        else cout << ans[(k-st)%m+st] << endl;
    }
    return 0;
}