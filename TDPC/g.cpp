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
const ll INF = (1LL << 61);
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

void add(long long &a, long long b) { a += b; if (a >= INF) a = INF; }

void dynamic_problem(string &s, vector<vector<long long>> &dp){
    int n = s.size();
    dp[n-1][s[n-1]-'a'] = 1;
    for(int i=n-2; i>=0; --i){
        rep(j, 26){
            if(s[i]-'a'==j){
                dp[i][j] = 1;
                rep(k, 26){
                    add(dp[i][j], dp[i+1][k]);
                }
            }else{
                add(dp[i][j], dp[i+1][j]);
            }
        }
    }
}

string rec(string &s, vector<vector<long long>> &dp, long long K, int i){
    if(K<=0)return "";
    ll sum = 0;
    rep(j, 26){
        if(dp[i][j]<=K-sum){
            while(s[i]!=('a'+j))i++;
            return (char)('a'+j) + rec(s, dp, K - sum - 1, i);
        }
        sum += dp[0][j];
    }
    return "Eel";
}

string calc(string &s, vvll &dp, ll K){
    int n = s.size();
    string res = "" ;
    for (int i = 0; i < n; ++i) {
        // 次の文字が何かを決める
        int j;
        for (j = 0; j < 26; ++j) {
            if (K - dp[i][j] <= 0) break;
            K -= dp[i][j];
        }
        char c = 'a' + j; // 次の文字は c
        res += c;
        --K; // c をとって終了し、残りは何も取らないような文字列を除外
        if (K <= 0) break; // K <= 0  になるなら c で終了
        while (s[i] != c) ++i;
    }
    return res;
}

string solve(string &s, ll K){
    int n = s.size();
    vvll dp(n, vll(26, 0)); // dp[i][j]: i文字目以降で先頭がjである部分文字列の個数
    dynamic_problem(s, dp);
    string res;
    ll sum = 0;
    rep(j, 26) sum += dp[0][j];
    if(sum<K)res = "Eel";
    else res = calc(s, dp, K);
    return res;
}

int main(){
    string s;
    ll k;
    cin >> s >> k;
    cout << solve(s, k) << endl;
    return 0;
}