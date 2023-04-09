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

struct RollingHash {
    const int base = 9973;
    const vector<int> mod = {999999937LL, 1000000007LL};
    string S;
    vector<long long> hash[2], power[2];

    // construct
    RollingHash(){}
    RollingHash(const string &cs) { init(cs); }
    void init(const string &cs) {
        S = cs;
        int n = (int)S.size();
        for (int iter = 0; iter < 2; ++iter) {
            hash[iter].assign(n+1, 0);
            power[iter].assign(n+1, 1);
            for (int i = 0; i < n; ++i) {
                hash[iter][i+1] = (hash[iter][i] * base + S[i]) % mod[iter];
                power[iter][i+1] = power[iter][i] * base % mod[iter];
            }
        }
    }
    // get hash of S[left:right]
    inline long long get(int l, int r, int id = 0) const {
        long long res = hash[id][r] - hash[id][l] * power[id][r-l] % mod[id];
        if (res < 0) res += mod[id];
        return res;
    }
    // get lcp of S[a:] and S[b:]
    inline int getLCP(int a, int b) const {
        int len = min((int)S.size()-a, (int)S.size()-b);
        int low = -1, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid, 0) != get(b, b+mid, 0)) high = mid;
            else if (get(a, a+mid, 1) != get(b, b+mid, 1)) high = mid;
            else low = mid;
        }
        return low;
    }
    // get lcp of S[a:] and T[b:]
    inline int getLCP(const RollingHash &t, int a, int b) const {
        int len = min((int)S.size()-a, (int)S.size()-b);
        int low = -1, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid, 0) != t.get(b, b+mid, 0)) high = mid;
            else if (get(a, a+mid, 1) != t.get(b, b+mid, 1)) high = mid;
            else low = mid;
        }
        return low;
    }
};

int main(){
    int n;
    string t;
    cin >> n >> t;
    string a = t.substr(0, n);
    string b = t.substr(n, n);
    // cout << a << " " << b << endl;
    reverse(all(b));
    // a = t[:n], b = t[n:]
    string x = a+b;
    string y = b+a;
    RollingHash hx(x);
    RollingHash hy(y);
    rep(i, n+1){
        bool ok = true;
        rep(id, 2){
            if(hx.get(0, i, id) != hx.get(2*n-i, 2*n, id) || hy.get(0, n-i, id) != hy.get(n+i, 2*n, id))ok = false;
        }
        if(ok){
            string s = t.substr(i, n);
            reverse(all(s));
            cout << s << endl;
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}