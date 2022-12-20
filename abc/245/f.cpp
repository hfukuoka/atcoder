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

int n, m;
vector<vector<int>> g;
vector<vector<int>> rg;
vector<bool> seen1;
vector<bool> seen2;
vector<bool> fin;
vector<int> cr;
set<int> s;

void dfs1(int v, int p){
    for(auto nv:g[v]){
        // if(nv==p)continue;
        if(fin[nv])continue;
        if(seen1[nv] && !fin[nv]){
            cr.push_back(nv);
            return;
        }
        seen1[nv] = true;
        dfs1(nv, v);
    }
    fin[v] = true;
}

void dfs2(int v, int p){
    s.insert(v);
    for(auto nv:rg[v]){
        if(nv==p)continue;
        if(seen2[nv])continue;
        seen2[nv]=true;
        dfs2(nv, v);
    }
}

int main(){
    cin >> n >> m;
    g.resize(n);
    rg.resize(n);
    rep(i, m){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    seen1.assign(n, false);
    seen2.assign(n, false);
    fin.assign(n, false);
    rep(i,n){
        if(!seen1[i])dfs1(i, -1);
    }
    // for(auto v:cr)cout << v << endl;
    for(int i:cr){
        if(!seen2[i])dfs2(i, -1);
    }
    cout << s.size() << endl;
    return 0;
}