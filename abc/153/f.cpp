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

using S = long long;
S op(S a, S b){return 0;}
S e(){return 0;}
using F = long long;
S mapping(F f, S x){return x-f;}
F composition(F f, F g){return f+g;}
F id(){return 0;}

int main(){
    ll n, d, a;
    cin >> n >> d >> a;
    vector<Pll> ps(n);
    rep(i, n){
        ll x, h;
        cin >> x >> h;
        ps[i] = {x, h};
    }
    sort(all(ps));
    lazy_segtree<S, op, e, F, mapping, composition, id> segtree(n+5);
    vll xs(n);
    rep(i, n){
        auto [x, h] = ps[i];
        segtree.set(i, h);
        xs[i] = x;
    }
    ll ans = 0;
    rep(i, n){
        ll h = segtree.get(i);
        if(h<=0)continue;
        ll k = (h+a-1)/a; // k回爆弾を使う
        ans += k;
        int idx = upper_bound(all(xs), xs[i]+2*d) - xs.begin();
        segtree.apply(i, idx, a*k);
    }
    cout << ans << endl;
    return 0;
}