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
const int inf = 1<<30;
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

using S = int;
// 区間最大値を得るセグメント木
S opmax(int a, int b){
    return max(a, b);
};
S emax(){return -inf;}
// 区間最小値を得るセグメント木
S opmin(int a, int b){
    return min(a, b);
}
S emin(){return inf;}

int main(){
    int n;
    cin >> n;
    vector<int> p(n);
    rep(i, n){
        cin >> p[i];
        p[i]--;
    }
    segtree<S, opmax, emax> maxtree(n);
    segtree<S, opmin, emin> mintree(n);
    vector<int> ans(n, inf);
    rep(i, n){
        if(i>0){
            int res;
            res = maxtree.prod(0, p[i]);
            if(res!=-inf)chmin(ans[i], p[i]+i-res);
            res = mintree.prod(p[i], n);
            if(res!=inf)chmin(ans[i], -(p[i]-i)+res);
        }
        maxtree.set(p[i], p[i]+i);
        mintree.set(p[i], p[i]-i);
    }
    segtree<S, opmax, emax> mxt(n);
    segtree<S, opmin, emin> mnt(n);
    rep_down(i, n-1, 0){
        if(i<n-1){
            int res;
            res = mxt.prod(0, p[i]);
            if(res!=-inf)chmin(ans[i], p[i]-i-res);
            res = mnt.prod(p[i], n);
            if(res!=inf)chmin(ans[i], -(p[i]+i)+res);
        }
        mxt.set(p[i], p[i]-i);
        mnt.set(p[i], p[i]+i);
    }
    rep(i, n){
        cout << ans[i] << (i==n-1 ? '\n' : ' ');
    }
    return 0;
}