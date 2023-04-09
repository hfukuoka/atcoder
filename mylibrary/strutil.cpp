bool iscaibun(string s){
    int n = s.size();
    string rs = s;
    reverse(all(rs));
    rep(i, n/2)if(s[i]!=rs[i])return false;
    return true;
}