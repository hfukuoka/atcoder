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

ll l[200010] = {};
ll r[200010] = {};
int cur=1;

void dfs(const Graph &G, int v, int p) {
    if(G[v].size()==1 && (v!=0)){
        l[v] = cur;
        r[v] = cur;
        cur++;
        return;
    }
    ll le=INF, ri=0;
    for (auto nv : G[v]) {
        if (nv == p) continue;
        dfs(G, nv, v);
        chmax(ri, r[nv]);
        chmin(le, l[nv]);
    }
    l[v] = le;
    r[v] = ri;
    // cout << "h" << endl;
    return;
}

int main(){
    ll n;
    cin >> n;
    Graph G(n);
    rep(i, n-1){
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // rep(i, n){
    //     cout << i << endl;
    //     for(auto v : G[i]){
    //         cout << v <<  " ";
    //     }
    //     cout << endl;
    // }
    // cout << " h" << endl;
    dfs(G, 0, -1);
    rep(i, n){
        cout << l[i] << " " << r[i] << endl;
    }
    return 0;
}