#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;
vector<bool> seen;

int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n);
    vector<int> deg(n, 0);
    rep(i, m){
        int a, b;
        cin >> a >> b;
        g[b].push_back(a);
        deg[a]++;
    }
    rep(i, n)sort(g[i].begin(), g[i].end());
    queue<int> q;
    rep(i, n){
        if(deg[i]==0)q.push(i);
    }
    vector<int> order;
    while(!q.empty()){
        int v = q.front(); q.pop();
        order.push_back(v);
        for(auto nv:g[v]){
            deg[nv]--;
            if(deg[nv]==0)q.push(nv);
        }
    }
    reverse(order.begin(), order.end());
    rep(i, (int)order.size()){
        cout << order[i] << " ";
    }
    cout << endl;
    return 0;
}