#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

// Union-Find
struct UnionFind {
    vector<int> par, rank, siz;

    // 構造体の初期化
    UnionFind(int n) : par(n,-1), rank(n,0), siz(n,1) { }

    // 根を求める
    int root(int x) {
        if (par[x]==-1) return x; // x が根の場合は x を返す
        else return par[x] = root(par[x]); // 経路圧縮
    }

    // x と y が同じグループに属するか (= 根が一致するか)
    bool issame(int x, int y) {
        return root(x)==root(y);
    }

    // x を含むグループと y を含むグループを併合する
    bool unite(int x, int y) {
        int rx = root(x), ry = root(y); // x 側と y 側の根を取得する
        if (rx==ry) return false; // すでに同じグループのときは何もしない
        // union by rank
        if (rank[rx]<rank[ry]) swap(rx, ry); // ry 側の rank が小さくなるようにする
        par[ry] = rx; // ry を rx の子とする
        if (rank[rx]==rank[ry]) rank[rx]++; // rx 側の rank を調整する
        siz[rx] += siz[ry]; // rx 側の siz を調整する
        return true;
    }

    // x を含む根付き木のサイズを求める
    int size(int x) {
        return siz[root(x)];
    }
};

struct edge{
    int from;
    int to;
    int weight;
};

bool comp(const edge &e1, const edge &e2){
    return e1.weight < e2.weight;
}

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<edge> es(m);
    for(int i=0; i<m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        es[i] = {u, v, w};
    }
    sort(es.begin(), es.end(), comp);
    UnionFind uf(n);
    ll ans = 0;
    int cnt = 0;
    rep(i, m){
        auto [u, v, w] = es[i];
        if(uf.issame(u, v))continue;
        ans += w;
        uf.unite(u, v);
        cnt++;
        if(cnt==k)break;
    }
    if(cnt<k){
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}