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
const ll mod = 998244353;
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
    ll n;
    cin >> n;
    map<ll, ll> mp;
    vll v(n);
    ll m = 0;
    rep(i, n){
        ll d;
        v[i] = d;
        cin >> d;
        mp[d]++;
        chmax(m, d);
    }
    if((v[0]!=0) || (mp[0]!=1)){
        cout << "0\n" << endl;
        return 0;
    }
    ll ans = 1;
    for(ll d=1; d<=m; ++d){
        ans *= modpow(mp[d-1], mp[d], mod);
        if(ans == 0)break;
        ans %= mod;
    }
    cout << ans << "\n";
    return 0;
}