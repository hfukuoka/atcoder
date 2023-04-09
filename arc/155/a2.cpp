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

void out(bool f){
    cout << (f ? "Yes" : "No") << '\n';
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

    // get pair of hash of S[left:right]
    inline pair<long long, long long> get_pair(int l, int r) const {
        long long res0 = get(l, r, 0);
        long long res1 = get(l, r, 1);
        pair<long long, long long> res = make_pair(res0, res1);
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

void solsub(ll n, ll k, string &s){ // 1<=k<n のときの解法
    RollingHash h(s);
    string rs = s;
    reverse(all(rs));
    RollingHash hr(rs);
    bool ans = false;
    ll i = n-(n-k+1)/2;
    ll j = (n-k)/2;
    if(h.get_pair(i, n) == hr.get_pair(j, n-k)){ // s + s' の回文判定
        // cout << 1 << endl;
        if((h.get_pair(0, k) == h.get_pair(n-k, n)) && (h.get_pair(0, j) == hr.get_pair(k, i))){ // s' + s の回文判定
            ans = true;
        }
    }
    out(ans);
}

bool iscaibun(string s){
    int n = s.size();
    string rs = s;
    reverse(all(rs));
    rep(i, n/2)if(s[i]!=rs[i])return false;
    return true;
}

void solve(ll n, ll k, string &s){
    k %= 2*n;
    string rs = s;
    reverse(all(rs));
    string t;
    t.resize(k);
    rep(i, min(n, k))t[i] = rs[i];
    reverse(all(t));
    rep(i, min(n, k)){
        t[i] = s[i];
    }
    reverse(all(t));
    string s1 = s+t, s2 = t+s;
    if(iscaibun(s1) && iscaibun(s2))out(true);
    else out(false);
    return;
}

int main(){
    int t;
    cin >> t;
    rep(ti, t){
        ll n, k;
        string s;
        cin >> n >> k >> s;
        solve(n, k, s);
    }
    return 0;
}