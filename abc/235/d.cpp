#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep_up(i, a, n) for (ll i = a; i < n; ++i)
#define rep_down(i, a, n) for (ll i = a; i >= n; --i)
#define P pair<ll, ll>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>

const ll INF = (1ll << 60);
const ll mod = 1000000007;
const double pi = 3.14159265358979323846;
template <typename T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}


int main(){
    ll a, n;
    cin >> a >> n;
    ll m = 1;
    while(m <= n){
        m *= 10;
    }
    vector<ll> dist(m, -1);
    queue<ll> q;
    dist[1] = 0;
    q.push(1);
    ll cnt = 0;
    while(!q.empty()){
        cnt++;
        ll c = q.front();
        q.pop();
        ll dc = dist[c];
        ll op1 = a*c;
        if(op1 < m){
            if(dist[op1] == -1){
                dist[op1] = dc+1;
                q.push(op1);
            }
        }
        if(c >= 10){
            if(c%10 != 0){
                string s = to_string(c);
                ll len = s.size();
                char r = s[len-1];
                s.erase(len-1);
                s.insert(0, {r});
                ll op2 = atoi(s.c_str());
                if(op2 < m){
                    if(dist[op2]==-1){
                        dist[op2] = dc+1;
                        q.push(op2);
                    }
                }
            }
        }
    }
    cout << dist[n] << endl;
    return 0;
}