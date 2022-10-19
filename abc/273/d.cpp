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
    ll H, W;
    cin >> H >> W;
    ll rs, cs;
    cin >> rs >> cs;
    ll N;
    cin >> N;
    map<ll, vector<ll>> mr, mc;
    vll r(N), c(N);
    rep(i, N){
        cin >> r[i] >> c[i];
        mc[r[i]].push_back(c[i]);
        mr[c[i]].push_back(r[i]);
    }
    for(auto &x : mc){
        sort(all(x.second));
    }
    for(auto &y : mr){
        sort(all(y.second));
    }
    // for(auto x: mr){
    //     cout << "c" << x.first << endl;
    //     for(auto y: x.second){
    //         cout << y << endl;
    //     }
    // }
    ll q;
    cin >> q;
    ll rn=rs, cn=cs;
    rep(i, q){
        char d;
        ll l;
        cin >> d >> l;
        if(d=='L'){
            auto it = lower_bound(all(mc[rn]), cn);
            ll id = it - mc[rn].begin();
            if(id > 0){
                if(mc[rn][id-1]>=cn-l){
                    cn = mc[rn][id-1]+1;
                }else{
                    cn = max(cn - l, 1LL);
                }
            }else{
                    cn = max(cn - l, 1LL);
            }
        }
        if(d=='R'){
            auto it = lower_bound(all(mc[rn]), cn);
            if(it==mc[rn].end() || *it>cn+l){
                cn = min(cn+l, W);
            }else if(*it<=cn+l){
                cn = *it-1;
            }
        }
        if(d=='U'){
            auto it = lower_bound(all(mr[cn]), rn);
            ll id = it - mr[cn].begin();
            if(id > 0){
                if(mr[cn][id-1]>=rn-l){
                    rn = mr[cn][id-1]+1;
                }else{
                    rn = max(rn-l, 1LL);
                }
            }else{
                rn = max(rn-l, 1LL);
            }
        }
        if(d=='D'){
            auto it = lower_bound(all(mr[cn]), rn);
            if(it==mr[cn].end() || *it> rn+l){
                rn = min(rn+l, H);
            }else if(*it<= rn+l){
                rn = *it-1;
            }
        }
        cout << rn << " " << cn << endl;
    }
    return 0;
}