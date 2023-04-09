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


const int inf = 1<<30;

using S = int;
S op(S a, S b){return min(a, b);}
S e(){return inf;}
using F = int;
S mapping(F f, S x){return min(f, x);}
F composition(F f, F g){ // f(g(x))
    if(f==inf)return g;
    else return min(f, g);
}
F id(){return inf;}

int main(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    // 最小値で区間更新、一点取得
    lazy_segtree<S, op, e, F, mapping, composition, id> segtree(n+1); // a[i]:マスiからnまでいく最短手数。infならそこからnに行けない
    segtree.set(n, 0);
    rep_down(i, n, 0){
        if(s[i]=='1'){
            segtree.set(i, inf);
            continue;
        }
        ll cu = segtree.get(i);
        segtree.apply(max(0, i-m), i, cu+1);
    }
    if(segtree.get(0)==inf){
        cout << -1 << endl;
        return 0;
    }

    vector<int> ans;
    ll id = 0;
    ll cnt = segtree.get(0);
    rep_up(i, 1, n+1){
        ll res = segtree.get(i);
        if(res == cnt-1){
            ans.push_back(i-id);
            id = i;
            cnt--;
        }
    }

    for(auto a:ans){
        cout << a << " ";
    }
    cout << endl;
    return 0;
}