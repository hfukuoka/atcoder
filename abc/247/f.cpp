#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define ll long long
#define repll(i, n) for (ll i = 0; i < n; ++i)
#define rep_upll(i, a, n) for (ll i = a; i < n; ++i)
#define rep_downll(i, a, n) for (ll i = a; i >= n; --i)
#define Pll pair<ll, ll>
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep_up(i, a, n) for (int i = a; i < n; ++i)
#define rep_down(i, a, n) for (int i = a; i >= n; --i)
#define P pair<int, int>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define vvvi vector<vector<vector<int>>>
#define vvi vector<vector<int>>
#define vi vector<int>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>
#define pqi priority_queue<int>
#define pqgi priority_queue<int, vector<int>, greater<int>>
#define pb push_back
#define eb emplace_back

const ll INF = (1ll << 60);
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
template<typename Tx, typename Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
ll modpow(ll a, ll n, ll mod){
    if(n == 0) return 1;
    a %= mod;
    if(n % 2) return modpow(a, n-1, mod) * a % mod;
    else return modpow(a*a%mod, n/2, mod);
}
long long modDiv(long long a, long long b, long long m) {
	// Get the value of a/b
	return (a * modpow(b, m - 2, m)) % m;
}

vector<int> seen;
vector<vector<int>> G;
vector<int> c;


void dfs(int v, int id){
    seen[v] = true;
    c[id]++;
    for(auto nv:G[v]){
        if(seen[nv])continue;
        dfs(nv, id);
    }
}

using mint = modint998244353;

vector<mint> mf, mg;

mint f(int x){
    if(mf[x]!=-1)return mf[x];
    if(x==1) return mf[x] = 2;
    if(x==2) return mf[x] = 3;
    return mf[x] = f(x-1)+f(x-2);
}

mint g(int x){
    if(mg[x]!=-1)return mg[x];
    if(x==1) return mg[x] = 1;
    if(x==2) return mg[x] = 3;
    if(x==3) return mg[x] = 4;
    return mg[x] = f(x-1) + f(x-3);
}


int main(){
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    rep(i, n)cin >> p[i];
    rep(i, n)cin >> q[i];
    G.resize(n);
    rep(i, n){
        p[i]--, q[i]--;
        G[p[i]].push_back(q[i]);
        G[q[i]].push_back(p[i]);
    }
    seen.assign(n, false);
    rep(i, n){
        if(seen[i])continue;
        c.push_back(0);
        dfs(i, c.size()-1);
    }
    mf.assign(n+1, -1);
    mg.assign(n+1, -1);
    mint ans = 1;
    for(auto m:c) ans *= g(m);
    cout << ans.val() << endl;
    return 0;
}