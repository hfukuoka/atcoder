#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;

/* topo_sort(G): グラフG をトポロジカルソート
    返り値: トポロジカルソートされた頂点番号
    計算量: O(|E|+|V|)
 */
void dfs(const Graph &G, int v, vector<bool> &used, vector<int> &ans) {
    used[v] = true;
    for (auto nv : G[v]) {
        if (!used[nv]) {
            dfs(G, nv, used, ans);
        }
    }
    ans.push_back(v);  // 帰りがけにpush_back
}
vector<int> topo_sort(const Graph &G) {  // bfs
    vector<int> ans;
    int n = (int)G.size();
    vector<bool> used(n, false);
    for (int v = 0; v < n; v++) {  // 未探索の頂点ごとにDFS
        if (!used[v]) dfs(G, v, used, ans);
    }
    reverse(ans.begin(), ans.end());  // 逆向きなのでひっくり返す
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