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

long long modDiv(long long a, long long b, long long m) {
	// Get the value of a/b
	return (a * modpow(b, m - 2, m)) % m;
}

long long modSum1toX(long long X) {
	// Calculate 1 + 2 + ... + X mod 1000000007
	long long v1 = X % mod;
	long long v2 = (X + 1) % mod;
	long long v = v1 * v2 % mod;
	return modDiv(v, 2, mod);
}

using Graph = vector<vector<long long>>;

// 探索
vector<bool> seen, finished;

// サイクル復元のための情報
int pos = -1; // サイクル中に含まれる頂点 pos
stack<int> hist; // 訪問履歴

ll n, m;
set<string> st;
bool f = false;
vector<string> vs;

void dfs(vector<long long> &p, ll id, string ns) {
    if(f)return;
    ll l = ns.size();
    if(id==n){
        if(l>=3 && !st.count(ns)){
            cout << ns << endl;
            f = true;
            return;
        }
        return;
    }
    if(l==0){
        ll size = vs[p[id]].size();
        if(size<=16)dfs(p, id+1, ns+vs[p[id]]);
    }else if(ns[l-1]!='_'){
        if(l+1<=16)dfs(p, id, ns+"_");
    }else{
        if(l+1<=16)dfs(p, id, ns+"_");
        ll size = vs[p[id]].size();
        if(l+size<=16)dfs(p, id+1, ns+vs[p[id]]);
    }
    return;
}



int main(){
    cin >> n >> m;
    vs.resize(n);
    rep(i, n) cin >> vs[i];
    rep(i, m) {
        string t;
        cin >> t;
        st.insert(t);
    }
    vll p(n);
    rep(i, n)p[i]=i;
    // int remain = 16;
    // rep(i, n)remain -= vs[i].size();
    do {
        dfs(p, 0, "");
        if(f)return 0;
    }while(next_permutation(all(p)));
    cout << -1 << endl;
    return 0;
}