#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define ll long long
#define repll(i, n) for (ll i = 0; i < n; ++i)
#define rep_upll(i, a, n) for (ll i = a; i < n; ++i)
#define rep_downll(i, a, n) for (ll i = a; i >= n; --i)
#define Pll pair<ll, ll>
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep_up(i, a, n) for (int i = a; i < n; ++i)
#define rep_down(i, a, n) for (int i = a; i >= n; --i)
#define P pair<int, int>

#define all(v) v.begin(), v.end()
#define fi first
#define se second
#define vvvll vector<vector<vector<ll>>>
#define vvll vector<vector<ll>>
#define vll vector<ll>
#define vvvi vector<vector<vector<int>>>
#define vvi vector<vector<int>>
#define vi vector<int>
#define pqll priority_queue<ll>
#define pqllg priority_queue<ll, vector<ll>, greater<ll>>
#define pqi priority_queue<int>
#define pqgi priority_queue<int, vector<int>, greater<int>>
#define pb push_back
#define eb emplace_back

template<typename T>
void printv(vector<T> &v){
    for(auto e:v)cout << e << " ";
    cout << "\n";
}

const ll INF = (1ll << 60);
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
template<typename Tx, typename Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
ll mypow(ll a, ll n) {
    ll ret = 1;
    rep(i, n) {
        if (ret > (ll)(1e18 + 10) / a) return -1;
        ret *= a;
    }
    return ret;
}
ll modpow(ll a, ll n, ll mod){
    if(n == 0) return 1;
    a %= mod;
    if(n % 2) return modpow(a, n-1, mod) * a % mod;
    else return modpow(a*a%mod, n/2, mod);
}
long long modDiv(long long a, long long b, long long m) {
	// Get the value of a/b
	return (a * modpow(b, m - 2, m)) % m;
}

template<typename T>
vector<T> run_lengs(vector<T> &v){
    int n = v.size();
    vector<T> res;
    rep(i, n){
        if(i==n-1 || v[i]!=v[i+1])res.push_back(v[i]);
    }
    return res;
}

void solve(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    rep(i, n)cin >> a[i];
    rep(i, n)cin >> b[i];
    if(a==b){
        cout << "Yes" << endl;
        return;
    }
    b = run_lengs(b);
    int m = b.size();
    if(m!=1 && b[0]==b.back())b.pop_back(), m--;
    if(m==n){
        cout << "No" << endl;
        return;
    }
    // printv(b);
    rep(i, n){
        // printv(a);
        int k = 0;
        bool ok = true;
        rep(j, m){
            while(a[k]!=b[j]){
                k++;
                if(k==n){
                    ok = false;
                    break;
                }
            }
            if(!ok)break;
            // cout << k << endl;
        }
        if(ok){
            cout << "Yes" << endl;
            return;
        }
        rotate(a.begin(), a.begin()+1, a.end());
    }
    cout << "No" << endl;
    return;
}

int main(){
    int t;
    cin >> t;
    rep(ti, t)solve();
    return 0;
}