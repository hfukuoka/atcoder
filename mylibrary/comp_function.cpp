#include<bits/stdc++.h>
using namespace std;

bool asc_desc(pair<int, int>& left, pair<int, int>& right) {
    if (left.first == right.first) {
        return right.second < left.second;
    } else {
        return left.first  < right.first;
    }
}


// 第１引数を、ソート後配列の添字が小さい方に持っていきたい場合true/そうでない場合falseを返却するように実装する。
bool desc_asc(pair<int, int>& left, pair<int, int>& right) {
    if (left.first == right.first) {
        return left.second < right.second;
    } else {
        return right.first < left.first;
    }
}