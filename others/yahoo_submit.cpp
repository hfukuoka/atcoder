#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()

using mint = modint1000000007;

// 愚直解 O(n!n^2)
void simple_solve(vector<int> p){
    sort(all(p));
    int n = p.size();
    mint ans = 0;
    do{
        bool f = true;
        rep(i, n){
            int cnt = 0;
            for(int j=0; j<i; ++j){
                if(p[j]>p[i])cnt++;
            }
            if(cnt>=2)f = false;
        }
        if(f) ans++;
    }while(next_permutation(all(p)));
    cout << ans.val() << endl;
}

// 座標圧縮
vector<int> compress(vector<int> v){
    int n = v.size();
    vector<int> x = v;
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    vector<int> res(n);
    rep(i, n){
        res[i] = lower_bound(all(x), v[i]) - x.begin();
    }
    return res;
}

// 制約4の解法 O(nlogn)
void solve(vector<int> p){
    int n = p.size();
    p = compress(p); // 座標圧縮
    sort(all(p));
    int pre = -1;
    mint ans = 1;
    for(int i = 0; i<= p.back(); ++i){
        int cnt = upper_bound(all(p), i) - lower_bound(all(p), i);
        if(cnt<=1)continue;
        int k = i - pre; // 種類数
        ans *= mint(2).pow(k-1);
        if(i<p.back())ans *= cnt+1; // 連続部分に入り込む要素がある場合、どこに入るか
        pre = i;
    }
    int k = p.back() - pre;
    if(k>0)ans *= mint(2).pow(k-1);
    cout << ans.val() << endl;
}

int main(){
    int n;
    cin >> n;
    vector<int> p(n);
    rep(i, n)cin >> p[i];
    simple_solve(p);
    solve(p);
    return 0;
}