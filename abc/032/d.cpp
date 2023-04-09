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

ll N, W;
vll v, w;

void solve1(){ // 半分全列挙　O(2^(N/2))
    map<ll, ll> mp; // mp[i]:重さがiのときの価値の最大値
    rep(s, 1<<(N/2)){
        ll weight = 0;
        ll value = 0;
        rep(i, N/2){
            if(s>>i&1){
                weight += w[i];
                value += v[i];
            }
        }
        if(weight<=W)chmax(mp[weight], value);
    }
    ll mx = 0;
    for(auto [w, v]:mp){ // mp[i]を重さi以下で実現可能な価値の最大値になるように累積max
        if(!chmax(mp[w], mx))mx = v;
    }
    ll ans = 0;
    int sz = N-(N/2);
    rep(s, 1<<sz){
        ll weight = 0;
        ll value = 0;
        rep(i, sz){
            if(s>>i&1){
                weight += w[N-i-1];
                value += v[N-i-1];
            }
        }
        if(weight>W)continue;
        auto it = mp.upper_bound(W-weight);
        if(it==mp.begin())continue;
        it--;
        chmax(ans, it->second + value);
    }
    cout << ans << endl;
}

void solve2(){ // 全てのiでw[i]<=1000　dp[id][重さ]
    const int MAX = 1001 * N;
    vvll dp(N+1, vll(MAX, -1));
    dp[0][0] = 0;
    rep(i, N){
        rep(j, MAX){
            if(dp[i][j]==-1)continue;
            chmax(dp[i+1][j], dp[i][j]);
            if(j+w[i]<MAX)chmax(dp[i+1][j+w[i]], dp[i][j]+v[i]);
        }
    }
    ll ans = 0;
    rep(j, W+1){
        chmax(ans, dp[N][j]);
    }
    cout << ans << endl;
}

void solve3(){ // 全てのiでv[i]<=1000  dp[id][価値]
    const int MAX = 1001 * N;
    vvll dp(N+1, vll(MAX, INF)); // dp[i][j]:iまで見て価値をjになるのに必要な重さの最小値
    dp[0][0] = 0;
    rep(i, N){
        rep(j, MAX){
            if(dp[i][j]==INF)continue;
            chmin(dp[i+1][j], dp[i][j]);
            if(j+v[i]<MAX)chmin(dp[i+1][j+v[i]], dp[i][j]+w[i]);
        }
    }
    ll ans = 0;
    rep(j, MAX){
        if(dp[N][j]<=W)chmax(ans, (ll)j);
    }
    cout << ans << endl;
}

int main(){
    cin >> N >> W;
    v.resize(N);
    w.resize(N);
    bool fw = true;
    rep(i, N){
        cin >> v[i] >> w[i];
        if(w[i]>1000)fw = false;
    }
    int t;
    if(N<=30)solve1();
    else if(fw)solve2();
    else solve3();
    return 0;
}