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

using mint = modint1000000007;

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

int main(){
    int h, w;
    cin >> h >> w;
    vvll a(h, vll(w));
    vector<Pll> v(h*w);
    rep(i, h){
        rep(j, w){
            cin >> a[i][j];
            v[i*w+j] = {a[i][j], i*w+j};
        }
    }
    sort(all(v));
    mint ans = 0;
    vector dp(h, vector<mint>(w, mint(0))); // dp[i][j]：i, jに到達する経路の数
    for(auto [d, id]:v){ // aが小さい順に見ると、そのマスに入ってくる経路数は全て確定
        int i = id/w;
        int j = id%w;
        dp[i][j] += 1; // (i, j)が始点のときを追加
        ans += dp[i][j];
        rep(v, 4){
            int ni = i+di[v];
            int nj = j+dj[v];
            if(ni<0 || ni>=h || nj<0 || nj>=w)continue; // 枠外は不可能
            if(a[ni][nj]>a[i][j]){ // 自分より大きいマスに遷移可能
                dp[ni][nj] += dp[i][j];
            }
        }
    }
    cout << ans.val() << endl;
    return 0;
}