#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <bits/stdc++.h>
#include "data_structure/disjoint-sparse-table.hpp"

using namespace std;
int main(){
    int n, q;
    int64_t a[500000];
    cin >> n >> q;
    for(int i=0;i<n;++i) cin >> a[i];
    disjoint_sparse_table dst{n, a, [](auto x, auto y){ return x + y; }};

    while(q--){
        int l, r;
        cin >> l >> r;
        cout << dst.get(l, r+1) << endl;
    }
    return 0;
}
