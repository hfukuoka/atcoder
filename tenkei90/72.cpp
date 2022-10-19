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

int H, W;
int dx[4]={0, 1, 0, -1};
int dy[4]={1, 0, -1, 0};
bool used[20][20];
char c[20][20];

int dfs(int sx, int sy, int px, int py){
    if(sx==px && sy==py && used[px][py]) return 0;
    used[px][py] = true;

    int ret = -100000;
    for(int i=0; i<4; ++i){
        int nx = px + dx[i], ny = py + dy[i];
        if(nx<1 || ny<1 || nx>H || ny>W || c[nx][ny]=='#') continue;
        if((sx != nx || sy != ny) && used[nx][ny] == true)continue;
        int v = dfs(sx, sy, nx, ny);
        chmax(ret, v+1);
    }
    used[px][py] = false;
    return ret;
}

int main(){
    cin >> H >> W;
    for(int i=1; i<=H; ++i){
        for(int j=1; j<=W; ++j){
            cin >> c[i][j];
        }
    }

    int ans = -1;
    for(int i=1; i<=H; ++i){
        for(int j=1; j<=W; ++j){
            chmax(ans, dfs(i, j, i, j));
        }
    }
    if(ans <= 2) ans = -1;
    cout << ans << endl;
    return 0;
}