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

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, -1)); // g[i][j]: i->jがあった場合その辺番号ないとき-1
    vector<P> edge(m); // 辺番号から逆引き
    rep(i, m){
        int s, t;
        cin >> s >> t;
        s--, t--;
        g[s][t] = i;
        edge[i] = {s, t};
    }
    vll dist(n, -1);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    vector<P> prev(n, {-1, -1});
    while(!q.empty()){
        int v = q.front(); q.pop();
        rep(nv, n){
            if(dist[nv]!=-1)continue; // 最短路が求まっているときcontinue
            if(g[v][nv]==-1)continue;
            dist[nv] = dist[v]+1;
            q.push(nv);
            prev[nv] = {v, g[v][nv]};
        }
    }
    if(dist[n-1]==-1){
        rep(i, m)cout << -1 << endl;
        return 0;
    }
    vector<int> path;
    int cur = n-1;
    while(cur!=0){
        path.push_back(prev[cur].second);
        cur = prev[cur].first;
    }
    vector<int> ans(m, dist[n-1]); // 全て元々の最短路で初期化
    // 1からnまでの最短経路のパスのみが変わりうるのでそこだけチェック
    // O(n(n+m))
    for(int e:path){
        g[edge[e].first][edge[e].second] = -1;
        queue<int> q; q.push(0);
        vector<int> dis(n, -1); dis[0] = 0;
        while(!q.empty()){
            int v = q.front();q.pop();
            rep(nv, n){
                if(dis[nv]!=-1)continue;
                if(g[v][nv]==-1)continue;
                dis[nv] = dis[v] + 1;
                q.push(nv);
            }
        }
        ans[e] = dis[n-1];
        g[edge[e].first][edge[e].second] = e;
    }
    rep(i, m){
        cout << ans[i] << '\n';
    }
    return 0;
}