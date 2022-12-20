#include<bits/stdc++.h>
using namespace std;

#define ll long long
using Graph = vector<vector<int>>;


// 二部グラフ判定、それぞれの色の個数を返す (黒の個数, 白の個数) O(n+m)
vector<int> color; // 各点の色を表す (0 or 1)
pair<ll, ll> dfs(const Graph &G, int v, int p, int c) {
    pair<ll, ll> ret = {0, 0};
    color[v] = c;
    if(c==0)ret.first++;
    else ret.second++;
    int nc = 1-c;
    for (auto nv : G[v]) {
        if(p==nv || color[nv]==nc)continue; // すでにカウント済みのところは飛ばす
        // 隣接頂点がすでに色確定していた場合
        if (color[nv] == c) return {-1, -1}; // 同じ色が隣接したらダメ

        pair<ll, ll> res = dfs(G, nv, v, nc);
        // 隣接頂点の色を変えて、再帰的に探索 (一回でも false が返ってきたら false)
        if(res.first==-1)return {-1, -1};
        ret.first += res.first;
        ret.second += res.second;
    }
    return ret;
}