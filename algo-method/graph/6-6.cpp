#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;

int main(){
    int n;
    cin >> n;
    Graph g(n);
    rep(i, n-1){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    int ans;
    while(!q.empty()){
        int v=q.front(); q.pop();
        int cnt = 0;
        for(auto nv:g[v]){
            if(dist[nv]!=-1)continue;
            dist[nv] = dist[v]+1;
            q.push(nv);
            cnt++;
        }
        if(cnt==0){
            ans = dist[v];
            break;
        }
    }
    cout << ans+1 << endl;
    return 0;
}