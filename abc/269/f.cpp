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

ll n, m, q;

using mint = modint998244353;

mint tousasum(mint c, mint d, mint k){ // 初項c, 公差d, 項数kの等差数列の和
    return k*(2*c+(k-1)*d)/mint(2);
}

mint a(ll x, ll y){ // 偶数行目の和
    mint s = mint((x+1)/2); // x方向に何個足すか？
    mint t = mint((y+1)/2); // y方向に何個足すか？
    mint c = tousasum(1, mint(2*m), s);
    return tousasum(c, mint(2*s), t);
}

mint b(ll x, ll y){ // 奇数行目の和
    mint s = mint(x/2);
    mint t = mint(y/2);
    if(s==0 || t==0)return mint(0);
    mint c = tousasum(1+m+1, 2*m, s);
    return tousasum(c, mint(2*s), t);
}

mint s(ll x, ll y){ // 0<=i<x, 0<=j<yのマス(i, j)の和
    if(x==0 || y==0)return mint(0);
    return a(x, y) + b(x, y);
}

void solve(){
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--; // 0index
    mint res = s(b+1, d+1) - s(a, d+1) - s(b+1, c) + s(a, c);
    cout << res.val() << '\n';
    return;
}

int main(){
    cin >> n >> m >> q;
    rep(qi, q)solve();
    return 0;
}