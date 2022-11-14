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
#define pb push_back
#define eb emplace_back

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

// const int MAXN = 1005;
// const int MAXV = MAXN * (MAXN-1)/2;
// vector<int> to[MAXV];
// int id[MAXN][MAXN];

// int toId(int i, int j){ // (i, j)の試合の頂点番号
//     if(i>j)swap(i, j);
//     return id[i][j];
// }

// bool visited[MAXV];
// bool finished[MAXV];
// int dp[MAXV];

// int dfs(int v){
//     if(visited[v]){
//         if(!finished[v])return -1;
//         return dp[v];
//     }
//     visited[v]=true;
//     dp[v] = 1;
//     for(auto u: to[v]){
//         int res = dfs(u);
//         if(res==-1)return -1;
//         dp[v] = max(dp[v], res+1);
//     }
//     finished[v] = true;
//     return dp[v];
// }

int main(){
    int n;
    cin >> n;
    vvi a(n, vi(n-1));
    rep(i, n){
        rep(j, n-1){
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    int V=0;
    rep(i, n)rep(j, n){
        if(i<j){
            id[i][j] = V++;
        }
    }
    rep(i, n){
        rep(j, n-1){
            a[i][j] = toId(i, a[i][j]);
        }
        rep(j, n-2){
            to[a[i][j+1]].push_back(a[i][j]);
        }
    }
    int ans = 0;
    rep(i, V){
        int res = dfs(i);
        if(res==-1){
            cout << -1 << endl;
            return 0;
        }
        ans = max(ans,res);
    }
    cout << ans << endl;
    return 0;
}