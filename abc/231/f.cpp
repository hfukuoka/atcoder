#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define ll long long
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep_up(i, a, n) for (ll i = a; i < n; ++i)
#define rep_down(i, a, n) for (ll i = a; i >= n; --i)
#define P pair<ll, ll>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>

const ll INF = (1ll << 60);
const ll mod = 1000000007;
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
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

vector<int> compress(vector<int> v){
    int n = v.size();
    vector<int> x = v;
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    vector<int> res(n);
    rep(i, n){
        res[i] = lower_bound(all(x), v[i]) - x.begin();
    }
    return res;
}

bool asc_desc(pair<int, int>& left, pair<int, int>& right) {
    if (left.first == right.first) {
        return right.second < left.second;
    } else {
        return left.first  < right.first;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> as(n), bs(n);
    rep(i, n)cin >> as[i];
    rep(i, n)cin >> bs[i];
    as = compress(as);
    bs = compress(bs);

    vector<pair<int, int>> ps(n);
    rep(i, n)ps[i] = {as[i], bs[i]};
    sort(all(ps), asc_desc);

    fenwick_tree<int> t(n+5);
    ll ans = 0;
    rep(i, n){
        ll cnt = 1;
        while(i+1<n && ps[i]==ps[i+1])cnt++, i++; // 同じ(a, b)をカウントしていく
        auto [a, b] = ps[i];
        ans += cnt*((ll)t.sum(b, n+1)+cnt); // cnt*t.sum: cnt個の同じペアに対して, それまで記録したbで現在のb以上のものの個数 cnt*cnt:同じ(a, b)同士を選ぶ場合の個数
        t.add(b, cnt);
    }
    cout << ans << endl;
    return 0;
}