#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for(int i=0; i<n; ++i)

using Graph = vector<vector<int>>;

int main(){
    int n,m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    Graph g(n);
    rep(i, m){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    queue<int> q;
    vector<bool> seen(n, false);
    seen[s] = true;
    q.push(s);
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto nv:g[v]){
            if(seen[nv])continue;
            seen[nv] = true;
            q.push(nv);
        }
    }
    if(seen[t])cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
