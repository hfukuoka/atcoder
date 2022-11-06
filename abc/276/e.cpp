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
#define bit(x,i)(((x)>>(i))&1)

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

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

int main(){
    int h, w;
    cin >> h >> w;
    vector<vector<char>> c(h, vector<char>(w));
    int si, sj;
    rep(i, h)rep(j, w){
        cin >> c[i][j];
        if(c[i][j]=='S'){
            si=i;
            sj=j;
        }
    }
    vector<vector<bool>> seen(h, vector<bool>(w, false));
    auto bfs = [&](int ti, int tj, unordered_set<int> &st){
        queue<P> q;
        q.push({ti, tj});
        while(!q.empty()){
            auto [i, j] = q.front();
            q.pop();
            seen[i][j]=true;
            rep(v, 4){
                int ni = i+di[v];
                int nj = j+dj[v];
                if(ni<0 || ni>=h || nj<0 || nj>=w)continue;
                if(c[ni][nj]=='#')continue;
                if(seen[ni][nj])continue;
                if(ni==si && nj==sj)continue;
                if(st.count(ni*w+nj)){
                    cout << "Yes" << "\n";
                    return 1;
                }
                q.push({ni, nj});
                seen[ni][nj]=true;
            }
        }
        return 0;
    };
    unordered_set<int> st;
    rep(d, 4){
        int ti = si+di[d];
        int tj = sj+dj[d];
        if(ti<0 || ti>=h || tj<0 || tj>=w)continue;
        if(c[ti][tj]=='#')continue;
        st.insert(ti*w+tj);
    }
    rep(d, 3){
        int ti = si+di[d];
        int tj = sj+dj[d];
        if(ti<0 || ti>=h || tj<0 || tj>=w)continue;
        if(c[ti][tj]=='#')continue;
        st.erase(ti*w+tj);
        int f = bfs(ti, tj, st);
        if(f)return 0;
    }
    cout << "No" << "\n";
    return 0;
}