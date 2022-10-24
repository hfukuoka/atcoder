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
    ll n;
    cin >> n;
    ll x, y;
    cin >> x >> y;
    vll a(n);
    rep(i, n)cin >> a[i];
    vvll dpx(n+1 ,vll(20010, 0)), dpy(n+1, vll(20010, 0));
    dpx[1][10000+a[0]] = 1;
    dpy[0][10000] = 1;
    rep(i, n){
        if(i==0)continue;
        rep(j, 20005){
            if(i%2==0){
                if(j+a[i]<20010)chmax(dpx[i+1][j+a[i]], dpx[i-1][j]);
                if(j-a[i]>=0)chmax(dpx[i+1][j-a[i]], dpx[i-1][j]);
                // dpy[i+1] = dpy[i];
            }else{
                if(j+a[i]<20010)chmax(dpy[i+1][j+a[i]], dpy[i-1][j]);
                if(j-a[i]>=0)chmax(dpy[i+1][j-a[i]], dpy[i-1][j]);
                // dpx[i+1] = dpx[i];
            }
        }
        // cout << "i: " << i << endl;
        // for(ll j=-10; j<=10; ++j){
        //     for(ll k=-10; k<=10; ++k){
        //         if(dpx[i][10000+j]==1 && dpy[i][10000+k]==1) cout << "1 ";
        //         else cout << "0 ";
        //     }
        //     cout << endl;
        // }
    }
    // cout << "i: " << n << endl;
    //     for(ll j=-10; j<=10; ++j){
    //         for(ll k=-10; k<=10; ++k){
    //             if(dpx[n][10000+j]==1 && dpy[n][10000+k]==1) cout << "1 ";
    //             else cout << "0 ";
    //         }
    //         cout << endl;
    //     }
    if((dpx[n][x+10000]==1 || dpx[n-1][x+10000]==1) && (dpy[n][y+10000]==1 || dpy[n-1][y+10000]==1)){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
    return 0;
}