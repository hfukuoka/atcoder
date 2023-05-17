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

// (i, j)の隣接する座標との差分のペア
pair<array<int, 6>, array<int, 6>> adjacent_diff(int i, int j){
    if(i%2==0){
        array<int, 6> di = {0, 1, 0, -1, -1, 1};
        array<int, 6> dj = {1, 0, -1, 0, -1, -1};
        return {di, dj};
    }else{
        array<int, 6> di = {0, 1, 0, -1, -1, 1};
        array<int, 6> dj = {1, 0, -1, 0, 1, 1};
        return {di, dj};
    }
}

int main(){
    int h, w;
    cin >> w >> h;
    int H = h+2;
    int W = w+2;
    vector<vector<int>> c(H, vector<int>(W, 0));
    rep(i, h)rep(j, w)cin >> c[i+1][j+1];
    int ans = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});
    vector<vector<int>> seen(H, vector<int>(W, 0));
    seen[0][0] = 1;
    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        auto [di, dj] = adjacent_diff(i, j);
        rep(v, 6){
            int ni = i+di[v];
            int nj = j+dj[v];
            if(ni<0 || ni>=H || nj<0 || nj>=W)continue;
            if(c[ni][nj]==1){
                ans++;
                // cout << ni << " " << nj << endl;
                continue;
            }
            if(seen[ni][nj])continue;
            seen[ni][nj] = 1;
            q.push({ni, nj});
        }
    }
    cout << ans << endl;
    return 0;
}