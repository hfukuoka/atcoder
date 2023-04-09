vector<int> compress(vector<int> v){
    int n = v.size();
    vector<int> x = v;
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    vector<int> res(n);
    rep(i, n){
        res[i] = lower_bound(all(x), v[i]) - x.begin();
    }
    return res;
}