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


int main(){
  ll n, x;
	cin >> n >> x;
  vll a(n);
  rep(i, n)cin >> a[i];
	vll dp(2, INF);
	dp[0] = 0;
	rep(i, n-1){
		ll d = a[i+1]/a[i];
		ll r = x%d;
		vll p(2, INF);
		swap(dp, p);
		rep(c, 2){
			rep(nc, 2){
				ll nr = c-nc*d+r;
				chmin(dp[nc], p[c]+abs(nr));
			}
		}
		x /= d;
	}
	ll ans = INF;
	rep(c, 2)chmin(ans, dp[c]+abs(x+c));
	cout << ans << endl;
  return 0;
}