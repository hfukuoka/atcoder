#include <bits/stdc++.h>
using namespace std;


/* 使い方
LCA<T> tree(n)　頂点数nで構造体を宣言
tree.addEdge(a, b, c)　(a, b) コストcの無向辺を作成
tree.init(root)　rootを根とするdfsして距離やコストなど必要な情報を計算 計算量：O(n)
tree.lca(a, b)　aとbのLCAを返す　O(1)
tree.length(a, b)　aからbの距離(辺ごとにコスト1)
tree.dist(a, b)　aからbの距離（辺ごとのコストで計算） */

template<typename T> // T: type of cost
struct LCA {
    int n, root, l;
    vector<vector<int>> to;
    vector<vector<T>> co;
    vector<int> dep;
    vector<T> costs;
    vector<vector<int>> par;
    LCA(int n):n(n),to(n),co(n),dep(n),costs(n) {
        l = 0;
        while ((1<<l) < n) ++l;
        par = vector<vector<int>>(n+1,vector<int>(l,n));
    }
    void addEdge(int a, int b, T c=0) { // (a, b) コストcの無向辺を作成
        to[a].push_back(b); co[a].push_back(c);
        to[b].push_back(a); co[b].push_back(c);
    }
    void dfs(int v, int d=0, T c=0, int p=-1) { // dfsして距離とコストを算出
        if (p != -1) par[v][0] = p;
        dep[v] = d;
        costs[v] = c;
        for (int i = 0; i < to[v].size(); ++i) {
            int u = to[v][i];
            if (u == p) continue;
            dfs(u, d+1, c+co[v][i], v);
        }
    }

    void init(int _root=0) { // _rootを根とする木を構築
        root = _root;
        dfs(root);
        for (int i = 0; i < l-1; ++i) {
            for (int v = 0; v < n; ++v) {
                par[v][i+1] = par[par[v][i]][i];
            }
        }
    }
    // LCA
    int lca(int a, int b) { // lcaを求める
        if (dep[a] > dep[b]) swap(a,b);
        int gap = dep[b]-dep[a];
        for (int i = l-1; i >= 0; --i) {
            int len = 1<<i;
            if (gap >= len) {
                gap -= len;
                b = par[b][i];
            }
        }
        if (a == b) return a;
        for (int i = l-1; i >= 0; --i) {
            int na = par[a][i];
            int nb = par[b][i];
            if (na != nb) a = na, b = nb;
        }
        return par[a][0];
    }
    int length(int a, int b) { // 1辺の長さ1のときの距離
        int c = lca(a,b);
        return dep[a]+dep[b]-dep[c]*2;
    }
    T dist(int a, int b) { // 辺ごとにコストがある場合の距離
        int c = lca(a,b);
        return costs[a]+costs[b]-costs[c]*2;
    }
};