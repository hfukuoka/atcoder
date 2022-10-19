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
    ll n, q;
    cin >> n >> q;
    vll t(q), x(q), y(q), v(q);
    vll c(n, -1), b(n);
    rep(i, q){
        cin >> t[i] >> x[i] >> y[i] >> v[i];
        x[i]--;
        y[i]--;
        if(t[i]==0)c[x[i]] = v[i];
    }
    rep(i, n){
        if(i==0){
            b[i] = 0;
            continue;
        }
        if(c[i-1]==-1){
            b[i] = 0;
            continue;
        }
        b[i] = c[i-1] - b[i-1];
    }
    dsu uf(n);
    rep(i, q){
        if(t[i]==0){
            uf.merge(x[i], y[i]);
        }else{
            if(uf.same(x[i], y[i])){
                ll ans;
                if((x[i]%2)==(y[i]%2)){
                    ans = b[y[i]]+v[i]-b[x[i]];
                }else{
                    ans = b[y[i]]-v[i]+b[x[i]];
                }
                cout << ans << endl;
            }else{
                cout << "Ambiguous" << endl;
            }
        }
    }
    return 0;
}