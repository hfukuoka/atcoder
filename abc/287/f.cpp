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

template<typename T>
void printv(vector<T> &v){
    for(auto e:v)cout << e << " ";
    cout << "\n";
}

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

using mint = modint998244353;
// dp[i][j] : 連結成分数がiで最後の頂点をj=0なら含んでいない, j=1なら含んでいる場合のVの個数
int n;
vector<vector<int>> g;

vector<vector<mint>> dfs(int v, int p){
    vector<vector<mint>> dp(2, vector<mint>(2, 0));
    dp[0][0] = 1;
    dp[1][1] = 1;
    for(auto nv:g[v]){
        if(nv==p)continue;
        auto ret = dfs(nv, v);
        vector<vector<mint>> ndp(2, vector<mint>(dp[0].size()+ret[0].size()-1, 0)); // 新しいdp配列
        // ndp[i][j]:vを根とした部分木の現在の子までを考えたときにi=1ならvを含むoなら含まない連結成分数がjの誘導グラフの数
        rep(i, dp[0].size()){ // 現在の連結成分数
            rep(j, ret[0].size()){ // 部分木の連結成分数
                ndp[0][i+j] += dp[0][i] * (ret[0][j] + ret[1][j]); // vで0なら子が0でも1でも全体で0 vで子の部分木同士はつながらず、連結成分数はi+j
                ndp[1][i+j] += dp[1][i] * ret[0][j]; // 子が0なら連結成分数は変わらない
                if(i+j>0) ndp[1][i+j-1] += dp[1][i] * ret[1][j]; // 子が１なら連結成分数は1減る
            }
        }
        swap(dp, ndp);
    }
    return dp;
}

int main(){
    cin >> n;
    g.resize(n);
    rep(i, n-1){
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    auto ret = dfs(0, -1);
    rep_up(i, 1, n+1){
        mint ans = ret[0][i] + ret[1][i];
        cout << ans.val() << endl;
    }
    return 0;
}