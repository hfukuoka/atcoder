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

bool solsub(vector<int> &v, int x){
    int s = 0;
    int n = v.size();
    rep(i, n)s += v[i];
    if(s<x || s%2!=x%2) return false;
    vector<int> dp(s+1, 0);
    dp[0] = 1;
    rep(i, n){
        vector<int> ndp(s+1, 0);
        rep(j, s+1){
            ndp[j] |= dp[j];
            if(j+v[i]<=s){
                ndp[j+v[i]] |= dp[j];
            }
        }
        swap(dp, ndp);
    }
    return dp[(s-x)/2];
}

void init(string &s, int &x, int &y, vector<int> &vx, vector<int> &vy){
    int n = s.size();
    int f = 0;
    int e = 0;
    bool tcome = false;
    rep(i, n){
        if(s[i]=='T'){
            if(f==0){
                if(tcome==false){
                    x -= e;
                    e = 0;
                    f = 1-f;
                    tcome = true;
                    continue;
                }
                vx.push_back(e);
                e = 0;
            }else if(f==1){
                vy.push_back(e);
                e = 0;
            }
            f = 1-f;
            continue;
        }
        e++;
    }
    if(e>0){
        if(tcome==false) x -= e;
        else if(f==0)vx.push_back(e);
        else if(f==1)vy.push_back(e);
    }
    x = abs(x);
    y = abs(y);
    return;
}

int main(){
    string s;
    cin >> s;
    int x, y;
    cin >> x >> y;
    vector<int> vx, vy;
    init(s, x, y, vx, vy);
    if(solsub(vx, x) && solsub(vy, y)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}