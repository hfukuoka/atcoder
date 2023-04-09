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
int h, w, t;
int si, sj, gi, gj;
vector<string> s;

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

vector<long long>dijkstra(ll x){
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    vll dist(h*w, INF);
    dist[si*w+sj] = 0;
    pq.push({dist[si*w+sj], si*w+sj});
    while(!pq.empty()){
        auto [d, v] = pq.top(); pq.pop();
        if(dist[v] < d)continue;
        int i = v/w;
        int j = v%w;
        rep(z, 4){
            int ni = i+di[z];
            int nj = j+dj[z];
            int nv = ni*w+nj;
            if(ni<0 || ni>=h || nj<0 || nj>=w)continue;
            ll cost;
            if(s[ni][nj]=='#')cost = x;
            else cost = 1;
            if(dist[nv] > dist[v]+cost){
                dist[nv] = dist[v]+cost;
                pq.push({dist[nv], nv});
            }
        }
    }
    return dist;
}

int main(){
    cin >> h >> w >> t;
    s.resize(h);
    rep(i, h)cin >> s[i];
    rep(i, h){
        rep(j, w){
            if(s[i][j]=='S'){
                si=i;
                sj=j;
            }
            if(s[i][j]=='G'){
                gi=i;
                gj=j;
            }
        }
    }
    ll ng = 1e9;
    ll ok = 1;
    int g = gi*w+gj;
    while(ng-ok>1){
        ll mid = (ok+ng)/2;
        auto check = [&](ll x){
            vll d = dijkstra(x);
            return d[g]<=t;
        };
        if(check(mid))ok = mid;
        else ng = mid;
    }
    cout << ok << endl;
    return 0;
}