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
vector<long long> fact, fact_inv, inv;
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

vector<int> compress(vector<int> v){
    int n = v.size();
    vector<int> x = v;
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    vector<int> res(n);
    rep(i, n){
        res[i] = lower_bound(all(x), v[i]) - x.begin();
    }
    return res;
}

void solve(vector<int> p){
    int n = p.size();
    p = compress(p); // 座標圧縮
    sort(all(p));
    int pre = -1;
    mint ans = 1;
    for(int i = 0; i<= p.back(); ++i){
        int cnt = upper_bound(all(p), i) - lower_bound(all(p), i);
        if(cnt<=1)continue;
        int k = i - pre; // 種類数
        ans *= mint(2).pow(k-1);
        if(i<p.back())ans *= cnt+1; // 連続部分に入り込む要素がある場合、どこに入るか
        pre = i;
    }
    int k = p.back() - pre;
    if(k>0)ans *= mint(2).pow(k-1);
    cout << ans.val() << endl;
}

int main(){
    int n;
    cin >> n;
    vector<int> p(n);
    rep(i, n)cin >> p[i];
    // solve(p);
    sort(all(p));
    int ans = 0;
    do{
        bool f = true;
        vector<int> v(n);
        rep(i, n){
            // cout << p[i] << " ";
            int cnt = 0;
            for(int j=0; j<i; ++j){
                if(p[j]>p[i])cnt++;
            }
            if(cnt>=2)f = false;
            v[i] = cnt;
        }
        // cout << endl;
        if(f){
            ans++;
            rep(i, n)cout << p[i] << " ";
            cout << endl;
            rep(i, n)cout << v[i] << " ";
            cout << endl;
            cout << endl;
        }
    }while(next_permutation(all(p)));
    cout << ans << endl;

    solve(p);
    return 0;
}