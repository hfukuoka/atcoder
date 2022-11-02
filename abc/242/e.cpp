#include <bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;

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

using Graph = vector<vector<long long>>;

// 探索
vector<bool> seen, finished;

// サイクル復元のための情報
int pos = -1; // サイクル中に含まれる頂点 pos
stack<int> hist; // 訪問履歴

void dfs(const Graph &G, int v, int p) {
    seen[v] = true;
    hist.push(v);
    for (auto nv : G[v]) {
        if (nv == p) continue; // 逆流を禁止する

        // 完全終了した頂点はスルー
        if (finished[nv]) continue;

        // サイクルを検出
        if (seen[nv] && !finished[nv]) {
            pos = nv;
            return;
        }

        // 再帰的に探索
        dfs(G, nv, v);

        // サイクル検出したならば真っ直ぐに抜けていく
        if (pos != -1) return;
    }
    hist.pop();
    finished[v] = true;
}

using mint = modint998244353;

int main(){
    ll t;
    cin >> t;
    vector<mint> power(1000000);
    power[0] = 1;
    rep(i, 1000000)power[i+1] = power[i]*(mint)26;
    // rep(i, 100)cout << power[i].val() << endl;
    while(t){
        t--;
        ll n;
        string s;
        cin >> n >> s;
        ll m = (n+1)/2;
        mint ans = 0;
        bool f = true;
        rep(i, m){
            int a = s[i]-'A';
            int b = s[n-i-1]-'A';
            // if(t==0)cout << s[i] << " " << s[n-i-1] << endl;
            mint cur;
            if(i==m-1){
                bool f=true;;
                ll l = i;
                while(l>=0){
                    int a = s[l]-'A';
                    int b = s[n-l-1]-'A';
                    if(a<b){
                        f = true;
                        break;
                    }else if(a>b){
                        f=false;
                        break;
                    }
                    l--;
                }
                cur = a;
                if(f)cur++;
                ans += cur;
                break;
            }
            cur = (mint)a*power[m-i-1];
            // if(t==0)cout << a << " "<< b<<" " << cur.val() << endl;
            ans += cur;
        }
        cout << ans.val() << endl;
    }
    return 0;
}