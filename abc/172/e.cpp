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

const int MOD = 1e9 + 7;
vector<long long> fact, fact_inv, inv; // fact[p]:p!, fact_inv[p]:(p!)^-1
/*  init_nCk :二項係数のための前処理
    計算量:O(n)
*/
void init_nCk(int SIZE) {
    fact.resize(SIZE + 5);
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact[0] = fact[1] = 1;
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
}
/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(1)
*/
long long nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
}

using mint = modint1000000007;

long long nPk(int n, int k){
    assert(!(n < k));
    return (fact[n] * fact_inv[n-k]) % MOD;
}

int main(){
    int n, m;
    cin >> n >> m;
    // 全体集合 U = {(A,B) | 全ての(i,j)(1<=i<j<=n) で A[i]!=A[j] かつ B[i]!=B[j]}
    // T_i = {(A,B) | A[i]=B[i]} T_iはUの部分集合
    // 求めたいのは |U| - |T_1 or T_2 or ... or T_n|

    mint uni = 0; // |T_1 or T_2 or ... or T_n|

    // 和集合の要素数を幇助原理で求める
    // T_iの積集合は対称性からandの個数が同じ場合は全て等しい
    // |T_1 or T_2 or ... or T_n| = nC1|T_1| - nC2|T_1 and T_2| + nC3|T_1 and T_2 and T_3| - ...

    init_nCk(m);
    for(int k=1; k<=n; ++k){
        mint crr = mint(nCk(n, k)) * mint(nPk(m, k)) * mint(nPk(m-k, n-k)) * mint(nPk(m-k, n-k));
        if(k%2) uni += crr; // 奇数個のandでは足す
        else uni -= crr; // 偶数個のandでは引く
    }
    mint ans = mint(nPk(m, n)).pow(2) - uni; // |U| - |T_1 or T_2 or ... or T_n|
    cout << ans.val() << endl;

    return 0;
}