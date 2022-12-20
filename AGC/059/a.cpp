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

using Graph = vector<vector<long long>>;

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) { // 前処理。spf を求める
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) { // nの素因数分解を求める
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};

template<typename T>
struct BIT {
    int n;
    vector<T> d;
    BIT(int n=0):n(n),d(n+1) {}
    void add(int i, T x=1) {
        for (i++; i <= n; i += i&-i) {
            d[i] += x;
        }
        }
    T sum(int i) {
        T x = 0;
        for (i++; i; i -= i&-i) {
            x += d[i];
        }
        return x;
    }
    T sum(int l, int r) {
        return sum(r-1) - sum(l-1);
    }
};

int n, q;
string s;
// map<tuple<int, int, int>, int> dp;
// map<tuple<int, int, int>, bool> cal;

// int solve(int l, int r, int c){
//     if(cal[{l, r, c}])return dp[{l,r,c}];
//     cal[{l, r, c}]=true;
//     if(l==r){
//         if(s[l]-'A'==c)dp[{l, r, c}]=0;
//         else dp[{l, r, c}]=1;
//         return dp[{l, r, c}];
//     }
//     int a = solve(l, r-1, c);
//     if(!(s[r]==s[r-1] || s[r]-'A'==c)) a++;
//     int b = solve(l+1, r, c);
//     if(!(s[l]==s[l+1] || s[l]-'A'==c)) b++;
//     dp[{l, r, c}] = min(a, b);
//     return dp[{l, r, c}];
// }


int main(){
    cin >> n >> q >> s;
    vvll dp(n+1, vll(3, 0));
    rep(c, 3)rep(i, n){
        dp[i+1][c] = dp[i][c];
        if(i==0){
            if(s[i]-'A'!=c)dp[i+1][c]++;
            continue;
        }
        if(s[i]-'A'!=c && s[i]!=s[i-1]){
            dp[i+1][c]++;
        }
    }
    rep(qi, q){
        int l, r;
        cin >> l >> r;
        r--;
        ll ans = 1<<30;
        // cout << qi << endl;
        while(l>0){
            l--;
            if(s[l]!=s[l-1])break;
        }
        rep(c, 3){
            chmin(ans, dp[r+1][c]-dp[l][c]);
            // cout << dp[r+1][c] << " " << dp[l][c] << endl;
        }
        cout << ans << endl;
    }
    return 0;
}