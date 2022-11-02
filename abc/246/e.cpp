#include <bits/stdc++.h>
using namespace std;

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

using Graph = vector<vector<long long>>;

// 探索
vector<bool> seen, finished;

// サイクル復元のための情報
int pos = -1; // サイクル中に含まれる頂点 pos
stack<int> hist; // 訪問履歴

void dfs(const Graph &G, int v, int p) {
    seen[v] = true;
    hist.push(v);
    for (auto nv : G[v]) {
        if (nv == p) continue; // 逆流を禁止する

        // 完全終了した頂点はスルー
        if (finished[nv]) continue;

        // サイクルを検出
        if (seen[nv] && !finished[nv]) {
            pos = nv;
            return;
        }

        // 再帰的に探索
        dfs(G, nv, v);

        // サイクル検出したならば真っ直ぐに抜けていく
        if (pos != -1) return;
    }
    hist.pop();
    finished[v] = true;
}

int dx[4] = {1, 1, -1, -1};
int dy[4] = {1, -1, 1, -1};

int main(){
    ll n;
    cin >> n;
    ll ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    ax--, ay--, bx--, by--;
    vector<string> s(n);
    rep(i, n)cin >> s[i];
    vvvll dis(n, vvll(n, vll(4, INF)));
    deque<pair<P, ll>> dq;
    rep(v, 4){
        ll cx = ax+dx[v];
        ll cy = ay+dy[v];
        if(cx<0 || cx>=n || cy<0 || cy>=n)continue;
        if(s[cx][cy]=='#')continue;
        dis[cx][cy][v]=1;
        dq.push_back({{cx, cy}, v});
    }
    vector seen(n, vector<vector<bool>>(n, vector<bool>(4, false)));
    while(!dq.empty()){
        auto [p, pv] = dq.front();
        auto [x, y] = p;
        if(x==bx && y==by){
            cout << dis[x][y][pv] << endl;
            return 0;
        }
        dq.pop_front();
        if(seen[x][y][pv])continue;
        seen[x][y][pv] = true;
        rep(v, 4){
            ll nx = x + dx[v];
            ll ny = y + dy[v];
            if(nx<0 || nx>=n || ny<0 || ny>=n)continue;
            if(s[nx][ny]=='#')continue;
            if(pv==v && dis[nx][ny][v]>dis[x][y][pv]){
                dis[nx][ny][v] = dis[x][y][pv];
                dq.push_front({{nx, ny}, v});
            }else if(pv!=v && dis[nx][ny][v]>dis[x][y][pv]+1){
                dis[nx][ny][v] = dis[x][y][pv]+1;
                dq.push_back({{nx, ny}, v});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}