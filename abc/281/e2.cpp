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

int n, m, k;
vll a;
ll sum=0;
multiset<int> s1, s2; // s1:小さいK個の集合, s2:それ以外

void del1(int i){
    auto it = s1.find(a[i]);
    s1.erase(it);
    sum -= *it;
}

void add1(int i){
    s2.insert(a[i]);
    auto it = s2.begin();
    sum += *it;
    s1.insert(*it);
    s2.erase(it);
}

void del2(int i){
    auto it = s2.find(a[i]);
    s2.erase(it);
}

void add2(int i){
    int mx = *s1.rbegin();
    if(mx>a[i]){
        sum -= mx;
        auto it = s1.find(mx);
        s1.erase(it);
        s2.insert(mx);
        sum += a[i];
        s1.insert(a[i]);
    }else{
        s2.insert(a[i]);
    }
}

int main(){
    cin >> n >> m >> k;
    a.resize(n);
    rep(i, n)cin >> a[i];
    vll b;
    rep(i, m)b.push_back(a[i]);
    sort(all(b));
    vll ans;
    rep(i, m){
        if(i<k){
            s1.insert(b[i]);
            sum += b[i];
        }else s2.insert(b[i]);
    }
    ans.push_back(sum);
    rep(i, n-m){
        auto it = s1.find(a[i]);
        if(it!=s1.end()){
            del1(i);
            add1(i+m);
        }else{
            del2(i);
            add2(i+m);
        }
        ans.push_back(sum);
    }
    rep(i, n-m+1){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}