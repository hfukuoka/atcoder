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

double dist(ll x1, ll y1, ll x2, ll y2){
    double ret = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    ret = sqrt((double)ret);
    return ret;
}

const double dinf = 1e18;

int V;
ll n, m;
double G[20][20];
double dp[1<<18][20];

double rec(int S, int v){
    if(S==0){
        if(v==0)return 0.0; //はじめ、どの頂点も訪問しておらず、最後の頂点は0であるべき
        else return dinf;
    }
    if((S & (1<<v)) == 0){ // 一度訪れた頂点をまた通るのはNG
        return dinf;
    }
    double &ret = dp[S][v];
    if(ret!=0.0) return ret; //メモされている場合はそれを使う
    ret = dinf;
    for(int u=0; u<V; ++u){
        if((1<<u)>=(1<<(n+1)))chmin(ret, rec(S ^ (1<<v), u)/2+G[u][v]); //宝箱の場合は今までのコストを半分にする
        else chmin(ret, rec(S ^ (1<<v), u)+G[u][v]);
    }
    return ret;
}

int main(){
    cin >> n >> m;
    V = n+m+1;
    vll x(n+m+1, 0), y(n+m+1, 0);
    rep(i, n) cin >> x[i+1] >> y[i+1];
    rep(i, m)cin >> x[n+i+1] >> y[n+i+1];
    rep(i, 20)rep(j, 20){
        G[i][j] = dinf;
    }
    rep(i, n+m+1){
        rep(j, n+m+1){
            G[i][j] = dist(x[i], y[i], x[j], y[j]);
            // cout << G[i][j] << " ";
        }
        // cout << endl;
    }
    double ans = dinf;
    for(int S=(1<<(n+1))-1; S<(1<<(n+m+1)); S += 1<<(n+1)){ // 0..01...1~1..11...1
        // cout << "S:" << S << endl;
        chmin(ans, rec(S, 0));
        // cout << ans << endl;
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}