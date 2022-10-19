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

struct node {
    ll p;
    ll c;
};
using Graph = vector<node>;

int main(){
    ll n, q;
    cin >> n >> q;
    Graph G(n, {p: -1, c:0});
    rep_up(i, 1, n){
        ll p; cin >> p;
        p--;
        G[i].p = p;
        G[p].c++;
    }
    while(q){
        ll m;
        cin >> m;
        vll v(m);
        ll k = 0;
        set<ll> st;
        rep(i, m){
            cin >> v[i];
            v[i]--;
            st.insert(v[i]);
        }
        ll ans=0;
        rep(i, m){
            if(!st.count(G[v[i]].p)){
                ans++;
                ans += G[v[i]].c;
            }else{
                ans--;
                ans += G[v[i]].c;
            }
        }
        cout << ans << endl;
        q--;
    }
    return 0;
}