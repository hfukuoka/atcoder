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

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

vector<int> cal(string s0, string s1){
    int w = s0.size();
    vector<int> res(w, 0);
    rep(j, w){
        if(j+1<w)if(s1[j+1]==s1[j])res[j]++;
        if(j-1>=0)if(s1[j-1]==s1[j])res[j]++;
        if(s1[j]==s0[j])res[j]++;
    }
    return res;
}

vector<int> judge(string s0, string s1, vector<int> v){
    int w = s0.size();
    int f0=1, f1=1; // f0:反転させない場合のokか f1: 反転させたらOKか
    rep(j, w){
        if(s0[j]==s1[j]){
            if(v[j]==0) f1 = 0;
        }else{
            if(v[j]==0) f0 = 0;
        }
    }
    vector<int> res = {f0, f1};
    return res;
}

pair<string, string> v2s(vector<int> &v){
    string s0 = "";
    string s1 = "";
    int n = v.size();
    rep(i, n){
        char c0 = '0'+v[i];
        char c1 = '0'+(1-v[i]);
        s0 += c0;
        s1 += c1;
    }
    return make_pair(s0, s1);
}

void init(map<pair<string, vector<int>>, ll> &dp, vector<int> &v){
    int w = v.size();
    vector<int> b(w, 0);
    rep(i, w){
        if(i+1<w)if(v[i]==v[i+1]){
            b[i]++;
            b[i+1]++;
        }
    }
    auto [s0, s1] = v2s(v);
    dp[{s0, b}] = 0;
    dp[{s1, b}] = 1;
}

int main(){
    int h, w;
    cin >> h >> w;
    vector a(h, vector<int>(w));
    rep(i, h)rep(j, w)cin >> a[i][j];
    map<pair<string, vector<int>>, ll> dp; 
    // dp[(s, v)]最後の文字列がs, その孤立度が配列vのとき、
    // その手前まで全て孤立していないようにするための必要な操作回数の最小値
    init(dp, a[0]);

    rep_up(i, 1, h){
        map<pair<string, vector<int>>, ll> ndp;
        auto [ns0, ns1] = v2s(a[i]);
        for(auto [p, val]:dp){
            vector<int> v = p.second; // 直前の行の孤立度
            string s = p.first; // 直前の行
            vector<int> res = judge(s, ns0, v); // 直前の行を現在の行をswapするかどうかで孤立させなくできるかどうか
            if(res[0]){ // swapしないで孤立させないようにできる場合
                vector<int> nv = cal(s, ns0); // 現在の行の孤立度を計算
                if(ndp.count({ns0, nv}))chmin(ndp[{ns0, nv}], val); 
                else ndp[{ns0, nv}] = val;
            }
            if(res[1]){ // swapして孤立させないようにできる場合
                vector<int> nv = cal(s, ns1);
                if(ndp.count({ns1, nv}))chmin(ndp[{ns1, nv}], val+1);
                else ndp[{ns1, nv}] = val+1;
            }
        }
        swap(dp, ndp);
    }
    ll ans = INF;
    for(auto [p, val]:dp){
        auto [s, v] = p;
        bool ok = true;
        rep(i, w)if(v[i]<=0){
            ok = false;
        }
        if(ok)chmin(ans, val);
        // cout << p.second << endl;
    }
    if(ans == INF) ans = -1;
    cout << ans << endl;
    return 0;
}