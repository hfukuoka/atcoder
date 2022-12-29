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
    int N, C;
    cin >> N >> C;
    vector<vector<pair<int, int>>> ps(C);
    rep(i, N){
        int s, t, c;
        cin >> s >> t >> c;
        c--;
        ps[c].push_back({s, t});
    }
    rep(c, C)sort(all(ps[c]));
    vector<int> tl(100010, 0);
    rep(c, C){
        int pre = -1;
        int sz = ps[c].size();
        rep(i, sz){
            if(i==0){
                auto [s, t] = ps[c][i];
                tl[s-1]++;
                tl[t]--;
                pre = t;
                continue;
            }
            auto [s, t] = ps[c][i];
            if(s==pre){
                tl[s]++;
                tl[t]--;
            }else{
                tl[s-1]++;
                tl[t]--;
            }
            pre = t;
        }
    }
    rep(i, 100009){
        tl[i+1] += tl[i];
    }
    int ans = 0;
    rep(i, 100010)chmax(ans, tl[i]);
    cout << ans << endl;
    return 0;
}