#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
typedef long long ll;

const int MAXN = 1005;
const int MAXV = MAXN*(MAXN-1)/2;
vector<int> to[MAXV];
int id[MAXN][MAXN];
int toId(int i, int j) {
  if (i > j) swap(i,j);
  return id[i][j];
}

bool visited[MAXV];
bool calculated[MAXV];
int dp[MAXV]; // max length of path from v
int dfs(int v) {
  if (visited[v]) {
    if (!calculated[v]) return -1;
    return dp[v];
  }
  visited[v] = true;
  dp[v] = 1;
  for (int u : to[v]) {
    int res = dfs(u);
    if (res == -1) return -1;
    dp[v] = max(dp[v], res+1);
  }
  calculated[v] = true;
  return dp[v];
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n-1));
  rep(i,n) {
    rep(j,n-1) {
      cin >> a[i][j];
      a[i][j]--;
    }
  }
  int V = 0;
  rep(i,n)rep(j,n) {
    if (i < j) {
      id[i][j] = V++;
    }
  }
  rep(i,n) {
    rep(j,n-1) {
      a[i][j] = toId(i,a[i][j]);
    }
    rep(j,n-2) {
      to[a[i][j+1]].push_back(a[i][j]);
    }
  }
  int ans = 0;
  rep(i,V) {
    int res = dfs(i);
    if (res == -1) {
      puts("-1");
      return 0;
    }
    ans = max(ans, res);
  }
  cout << ans << endl;
  return 0;
}