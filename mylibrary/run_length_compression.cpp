#include<bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> run_lengs(vector<T> &v){
    int n = v.size();
    vector<T> res;
    rep(i, n){
        if(i==n-1 || v[i]!=v[i+1])res.push_back(v[i]);
    }
    return res;
}