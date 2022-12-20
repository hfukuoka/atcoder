#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;

/* topo_sort(G): グラフG をトポロジカルソート
    返り値: トポロジカルソートされた頂点番号
    計算量: O(|E|+|V|)
 */
vector<int> topo_sort(const Graph &G) {  // bfs
    vector<int> ans;
    int n = (int)G.size();
    vector<int> ind(n);            // ind[i]: 頂点iに入る辺の数(次数)
    for (int i = 0; i < n; i++) {  // 次数を数えておく
        for (auto nv : G[i]) {
            ind[nv]++;
        }
    }
    queue<int> que;
    for (int i = 0; i < n; i++) {  // 次数が0の点をキューに入れる
        if (ind[i] == 0) {
            que.push(i);
        }
    }
    while (!que.empty()) {  // 幅優先探索
        int now = que.front();
        ans.push_back(now);
        que.pop();
        for (auto nv : G[now]) {
            ind[nv]--;
            if (ind[nv] == 0) {
                que.push(nv);
            }
        }
    }
    return ans;
}

int main(){
    int n, m;
    cin >> n >> m;
    Graph G(n);
    rep(i, m){
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }
    rep(i, n)sort(G[i].begin(), G[i].end());
    vector<int> ans = topo_sort(G);
    rep(i, n){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}