#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <bits/stdc++.h>
#include "data_structure/segment-tree.hpp"
#include "math/modint.hpp"
constexpr int64_t mod = 998244353;

using namespace std;
int main(){
    size_t n, q;
    cin >> n >> q;
    using Tp = pair<modint<mod>, modint<mod>>;
    static Tp a[500000];
    for(int i=0;i<n;++i){
        modint<mod> x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    
    segment_tree st{
        n,
        {modint<mod>{1}, modint<mod>{0}},
        [](const Tp &x, const Tp &y)->Tp{ return {x.first * y.first, x.second * y.first + y.second}; },
        a
    };
    while(q--){
        int t;
        cin >> t;
        if(t == 0){
            int p;
            modint<mod> c, d;
            cin >> p >> c >> d;
            st.set(p, {c, d});
        }else{
            int l, r;
            modint<mod> x;
            cin >> l >> r >> x;
            auto f = st.get(l, r);
            cout << f.first * x + f.second << "\n";
        }
    }
    return 0;
}
