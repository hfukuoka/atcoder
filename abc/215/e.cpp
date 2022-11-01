#include <bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep_up(i, a, n) for (ll i = a; i < n; ++i)
#define rep_down(i, a, n) for (ll i = a; i >= n; --i)

int main(){
    int n;
    string s;
    cin >> n >> s;
    vector dp(n+1, vector(1<<10, vector<mint>(10, 0))); // dp[i][s][j] iまで見て、最後に取った文字がjでとった集合がsの場合の総数

    rep_up(i,1,n+1){
        int x = s[i-1]-'A'; // 現在注目する文字
        // 最後の文字が変化しない遷移
        rep(s, 1<<10){
            rep(j, 10){
                dp[i][s][j] = dp[i-1][s][j]; //でないとき
                if(j==x)dp[i][s][j] += dp[i-1][s][j]; // 直前に出た場合に出るとき
            }
        }
        // 最後の文字が変化する遷移
        rep(s, 1<<10){
            if((s>>x)&1)continue; // xに今まででたことある場合continue
            rep(j, 10){
                dp[i][s|(1<<x)][x] += dp[i-1][s][j];
            }
        }
        dp[i][(1<<x)][x]+=1; // 初めて出る場合
    }
    mint ans = 0;
    rep(s, 1<<10){
        rep(j, 10)ans += dp[n][s][j];
    }
    cout << ans.val() << endl;
    return 0;
}