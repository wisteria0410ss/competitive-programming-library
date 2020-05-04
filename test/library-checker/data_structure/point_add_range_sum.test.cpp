#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
#include "data_structure/segment-tree.hpp"

using namespace std;
int main(){
    int n, q;
    static int64_t a[500000];
    cin >> n >> q;
    for(int i=0;i<n;++i) cin >> a[i];
    
    segment_tree st(n, INT64_C(0), [](auto x, auto y){ return x + y; }, a);
    while(q--){
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 0) st.add(l, r);
        else printf("%" PRId64 "\n", st.get(l, r));
    }
    return 0;
}