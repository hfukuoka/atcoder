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
// #define P pair<int, int>

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

ll N, P;

vvll warshall_floyd(vvll a, long long x){
    vvll d(N, vll(N, INF));
    rep(i, N){
        rep(j, N){
            if(a[i][j]==-1)d[i][j] = x;
            else d[i][j] = a[i][j];
        }
    }
    rep(k, N)rep(i, N)rep(j, N)chmin(d[i][j], d[i][k]+d[k][j]);

    return d;
}

ll binary_search(vvll &a, ll th){ // pスヌーク以下で到達できる頂点の組の個数f(x)について、f(x)<=thとなる最小のxは？？
    ll l = 0, r = INF;
    while(r-l>1){
        ll mid = (l+r)/2LL;
        vvll d = warshall_floyd(a, mid);
        ll cnt = 0;
        rep(i, N){
            rep(j, N){
                if(i>=j)continue;
                if(d[i][j]<=P)cnt++;
            }
        }
        if(cnt<=th)r = mid;
        else l = mid;
    }
    return r;
}

int main(){
    ll K;
    cin >> N >> P >> K;
    vvll a(N, vll(N));
    rep(i, N)rep(j, N)cin >> a[i][j];
    ll s = binary_search(a, K);
    ll t = binary_search(a, K-1);
    if(t-s>(1LL<<40)){
        cout << "Infinity" << endl;
        return 0;
    }
    ll ans = t - s;
    cout << ans << endl;
    return 0;
}