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

using mint = modint998244353;

bool isLowerCase(char c){
    if('a' <= c && c <= 'z')return true;
    else return false;
}

int main(){
    int n;
    string s;
    cin >> n >> s;
    vector dp(26, vector<mint>(26, 0));
    vector<int> id1, id2;
    if(s[0]=='?'){
        rep(i, 26)id1.push_back(i);
    }else id1.push_back(s[0]-'a');
    if(s[1]=='?'){
        rep(i, 26)id2.push_back(i);
    }else id2.push_back(s[1]-'a');
    for(auto i:id1){
        for(auto j:id2){
            if(i==j)continue;
            dp[i][j] = 1; // 今の文字がj, 直前の文字がjのときの総数
        }
    }
    rep_up(i, 2, n){
        vector ndp(26, vector<mint>(26, 0));
        if(isLowerCase(s[i])){
            int l = s[i]-'a';
            rep(j, 26){
                rep(k, 26){
                    if(j!=k && k!=l && l!=j)ndp[k][l] += dp[j][k];
                }
            }
        }else{
            rep(j, 26){
                rep(k, 26){
                    rep(l, 26){
                        if(j!=k && k!=l && l!=j)ndp[k][l] += dp[j][k];
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    mint ans = 0;
    rep(i, 26){
        rep(j, 26){
            if(i==j)continue;
            ans += dp[i][j];
        }
    }
    cout << ans.val() << endl;
    return 0;
}