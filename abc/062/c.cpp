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

ll sol1(ll h, ll w){
    ll w1 = w/3;
    ll w2 = (w-w1)/2;
    ll w3 = w-w1-w2;
    return h*w3-h*w1;
}

ll sol2(ll h, ll w){
    ll l = 0, r = w;
    while(r-l>1){
        ll x = (r+l)/2;
        if(h*(w-1)<=(1+h)*x)r = x;
        else l = x;
    }
    ll ans = INF;
    rep_up(x, max(1LL, l-10000), min(w-1, l+10000)){
        ll s1 = h/2*(w-x);
        ll s2 = (h-h/2)*(w-x);
        ll s3 = h*x;
        ll smin = min(s1, s3);
        ll smax = max(s2, s3);
        chmin(ans, smax-smin);
    }
    return ans;
}

int main(){
    int h, w;
    cin >> h >> w;
    ll ans = INF;
    chmin(ans, sol1(h, w));
    chmin(ans, sol1(w, h));
    chmin(ans, sol2(h, w));
    chmin(ans, sol2(w, h));
    cout << ans << endl;
    return 0;
}