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

const ll INF = (1ll << 62);
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
    int n, K;
    cin >> n >> K;
    vector<P> ps(n);
    rep(i, n){
        int x, y;
        cin >> x >> y;
        ps[i] = {x, y};
    }
    sort(all(ps)); // x軸方向にソート
    ll ans = INF;
    rep(i, n){
        ll L = ps[i].first;
        int cnt = 1;
        rep_up(j, i+1, n){
            ll R = ps[j].first;
            rep_up(k, i, j+1){ // kがiからjのときL<=x<=Rである
                ll D = ps[k].second;
                rep_up(l, i, j+1){
                    if(l==k)continue;
                    ll U = ps[l].second;
                    if(D>=U)continue;
                    ll cnt = 0;
                    rep_up(m, i, j+1){
                        if(D<=ps[m].second && ps[m].second<=U)cnt++;
                    }
                    if(cnt>=K){
                        chmin(ans, (R-L)*(U-D));
                        // cout << "l:" << L << " r:" << R << " d:" << D << " u:" << U << endl;
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}