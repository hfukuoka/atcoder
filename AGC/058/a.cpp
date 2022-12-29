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

bool isSmall(vector<int> &p, int i){
    int n = p.size();
    bool f = true;
    if(i+1<2*n)if(p[i]>p[i+1])f = false;
    if(i-1>=0)if(p[i-1]<p[i]) f = false;
    return f;
}

bool isBig(vector<int> &p, int i){
    int n = p.size();
    bool f = true;
    if(i+1<2*n)if(p[i]<p[i+1])f = false;
    if(i-1>=0)if(p[i-1]>p[i]) f = false;
    return f;
}

void myswap(vector<int> &p, vector<int> &inv, int i, vector<int> &x){
    inv[p[i]] = i+1;
    inv[p[i+1]] = i;
    swap(p[i], p[i+1]);
    x.push_back(i);
}

int main(){
    int n;
    cin >> n;
    vector<int> p(2*n);
    vector<int> inv(2*n);
    rep(i, 2*n){
        cin >> p[i];
        p[i]--;
        inv[p[i]] = i;
    }
    vector<int> t = p;
    int cnt = 0;
    int a = -1;
    vector<int> x;
    while(cnt<n){
        a++;
        int i = inv[a];
        if(i%2==0){
            cnt++;
            continue;
        }
        if(isBig(p, i))continue;
        if(i+1<2*n){
            if(p[i]<p[i+1]){
                myswap(p, inv, i, x);
                cnt++;
                continue;
            }
        }
        if(i-1>=0){
            if(p[i-1]>p[i]){
                myswap(p, inv, i-1, x);
                cnt++;
                continue;
            }
        }
    }
    int k = x.size();
    cout << k << '\n';
    rep(i, k){
        cout << x[i]+1 << (i==k-1 ? '\n' : ' ' );
    }
    rep(i, k){
        swap(t[x[i]], t[x[i]+1]);
    }
    // rep(i, 2*n){
    //     cout << t[i]+1 << " ";
    // }
    // cout << endl;
    return 0;
}