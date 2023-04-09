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

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    vll v(n);
    rep(i, n)cin >> v[i];
    vector dp(n+1, vector<pair<ll, ll>>(n+1, {-1, 0}));
    dp[0][0] = {0, 1};
    rep(i, n){
        rep(j, n){
            if(dp[i][j].first==-1)continue;
            if(dp[i+1][j].first == dp[i][j].first) dp[i+1][j].second += dp[i][j].second;
            if(chmax(dp[i+1][j].first, dp[i][j].first))dp[i+1][j].second = dp[i][j].second;
            if(j+1<=n){
                if(dp[i+1][j+1].first == dp[i][j].first + v[i])dp[i+1][j+1].second += dp[i][j].second;
                if(chmax(dp[i+1][j+1].first, dp[i][j].first+v[i])) dp[i+1][j+1].second = dp[i][j].second;
            }
        }
    }
    ll mx = -1, sum = 0;
    ll cnt = 0;
    for(ll i=a; i<=b; ++i){
        if(mx*i == dp[n][i].first*sum){
            cnt += dp[n][i].second;
        }else if(mx*i < dp[n][i].first*sum){
            cnt = dp[n][i].second;
            mx = dp[n][i].first;
            sum = i;
        }
    }
    double ans = (double)mx/sum;
    printf("%.10f\n", ans);
    cout << cnt << endl;
    return 0;
}