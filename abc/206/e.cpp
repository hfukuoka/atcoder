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

    // U = {(x, y) | L<=x<=R and L<=y<=R}
	// A = {(x, y) | g = gcd(x, y) = 1}
    // B = {(x, y) | g = gcd(x, y) = x}
    // C = {(x, y) | g = gcd(x, y) = y}

    // 対称性から |B| = |C|, |A&B| = |A&C|

	ll L, R;
    cin>>L>>R;
    ll res = (R - L + 1) * (R - L + 1); // |U|
    vector<vector<int> > p_factor(R + 1);
    for(int i = 2; i <= R; ++i){
        if(p_factor[i].empty()){
            for(int j = i; j <= R; j += i) p_factor[j].push_back(i);
        }
    }

    // |A|
    ll coprime_xy = 0;
    for(int x = L; x <= R; ++x){
        ll not_co_prime = 0; // xと互いに素でないL<=y<=R
        int sz = p_factor[x].size(); // xの素因数の種類数
        rep(s, 1<<sz){ // 各素因数を含むか含まないかを表すビットs
            if(s==0)continue;
            ll num = 1;
            rep(i, sz)if(s>>i&1){
                int p = p_factor[x][i]; // xの素因数p
                num *= p;
            }
            if(__builtin_popcount((unsigned int)s)%2==1)not_co_prime += R / num - (L-1) / num; // yがnumの倍数である個数
            else not_co_prime -= R / num - (L-1) / num;
        }
        coprime_xy += R - (L-1) - not_co_prime;
    }
    res -= coprime_xy;

    // |B| + |C| = 2*|B|
    for(int g=L; g<=R; ++g) res -= ((R/g) - (L-1)/g) * 2;

    // |A&B| + |A&C| = 2 * |A&B|
    if(L==1) res += (R-L+1) * 2;

    // |B&C|
    res += (R-L+1);

    // |A&B&C|
    if(L==1)res -= 1;

    cout << res << endl;
    return 0;
}