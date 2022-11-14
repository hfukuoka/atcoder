#include <bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rep1(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < (t); ++i)
#define rng(a) a.begin(),a.end()
#define rrng(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
#define newline puts("")
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
template<typename T> using PQ = priority_queue<T,vc<T>,greater<T>>;
using uint = unsigned; using ull = unsigned long long;
using vi = vc<int>; using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>;
using P = pair<int,int>; using vp = vc<P>; using vvp = vv<P>;
int geti(){int x;scanf("%d",&x);return x;}
vi pm(int n, int s=0) { vi a(n); iota(rng(a),s); return a;}
template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const T&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.fi>>v.se;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.fi<<","<<v.se;}
template<typename T1,typename T2>void operator--(pair<T1,T2>&a,int){a.fi--;a.se--;}
template<typename T>void operator--(vc<T>&a,int){for(T&x:a)x--;}
template<typename T>void operator+=(vc<T>&a,T b){for(T&x:a)x+=b;}
template<typename T>void operator+=(vc<T>&a,const vc<T>&b){a.insert(a.end(),rng(b));}
template<typename T1,typename T2>bool mins(T1& x,const T2&y){if(x>y){x=y;return true;}else return false;}
template<typename T1,typename T2>bool maxs(T1& x,const T2&y){if(x<y){x=y;return true;}else return false;}
template<typename Tx, typename Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
template<typename T>ll suma(const vc<T>&a){ll res(0);for(auto&&x:a)res+=x;return res;}
template<typename T>ll suma(const vv<T>&a){ll res(0);for(auto&&x:a)res+=suma(x);return res;}
template<typename T>void uni(T& a){sort(rng(a));a.erase(unique(rng(a)),a.end());}
template<typename T>void prepend(vc<T>&a,const T&x){a.insert(a.begin(),x);}
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("-1"); return;}
#define yes { puts("Yes"); return;}
#define no { puts("No"); return;}
#define ret(x) { cout<<(x)<<endl; return;}
#define yn {puts("Yes");}else{puts("No");}
const int MX = 200005;

struct Solver {
  void solve() {
    int a,b;
    scanf("%d%d",&a,&b);
    int ans = dup(b,a)*a-b;
    if (a < 32000) {
      rep(x,a) {
        int na = a+x;
        mins(ans, x+(dup(b,na)*na-b));
      }
    } else {
      int c = b/a;
      while (c >= 1) {
        int nb = dup(b,c)*c;
        mins(ans, (nb-b)+(nb/c-a));
        --c;
      }
    }
    cout<<ans<<endl;
  }
};

int main() {
  int ts = 1;
  scanf("%d",&ts);
  rep1(ti,ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}
