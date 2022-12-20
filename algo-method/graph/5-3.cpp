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
    vector<int> prev(n, -1);
    seen[s] = true;
    q.push(s);
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto nv:g[v]){
            if(seen[nv])continue;
            seen[nv] = true;
            prev[nv] = v;
            q.push(nv);
        }
    }
    vector<int> p;
    int crr = t;
    while(crr != -1){
        p.push_back(crr);
        crr = prev[crr];
    }
    reverse(p.begin(), p.end());
    int sz = p.size();
    cout << sz << endl;
    rep(i, sz){
        cout << p[i] << " ";
    }
    cout << endl;
    return 0;
}
