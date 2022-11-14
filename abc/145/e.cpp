#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
#define chmax(x,y) x = max(x,y)

int dp[3005][3005];

int main() {
  int n, t;
  cin >> n >> t;
  vector<P> p(n);
  rep(i,n) {
    cin >> p[i].first >> p[i].second;
  }
  sort(p.begin(), p.end());
  int ans = 0;
  rep(i,n) {
    rep(j,t) {
      chmax(dp[i+1][j], dp[i][j]);
      int nj = j+p[i].first;
      if (nj < t) chmax(dp[i+1][nj], dp[i][j]+p[i].second);
    }
    int now = dp[i][t-1]+p[i].second;
    chmax(ans, now);
  }
  rep(i, n+1){
    rep(j, t+1){
        if(dp[i][j]!=0){
            cout << j << ": ";
            cout << dp[i][j] << " ";
        }
    }
    cout << endl;
  }
  cout << ans << endl;
  return 0;
}