#define PROBLEM ""

#include <bits/stdc++.h>
#include "data_structure/lazy-segment-tree.hpp"
#include "math/modint.hpp"
constexpr int64_t mod = 998244353;

using namespace std;
int main(){
    size_t n;
    int q;
    cin >> n >> q;

    using Tp = modint<mod>;
    using Op = pair<modint<mod>, modint<mod>>;
    segment_tree<Tp, Op> st{ n,
        Tp{0},      [](const auto &lhs, const auto &rhs)->Tp{ return lhs + rhs; },
        Op{1, 0},   [](const auto &lhs, const auto &rhs)->Op{ return { lhs.first * rhs.first, lhs.first * rhs.second + lhs.second }; },
        [](auto f, auto x, size_t w)->Tp{ return f.first * x + f.second * w; }
    };
    vector<Tp> a;
    a.reserve(n);
    for(size_t i = 0; i < n; ++i){
        int val;
        cin >> val;
        a.emplace_back(val);
    }
    st.init(a.begin().base());

    while(q--){
        int tp, l, r, b, c;
        cin >> tp;
        if(tp == 0){
            cin >> l >> r >> b >> c;
            st.set(l, r, {b, c});
        }else{
            cin >> l >> r;
            cout << st.get(l, r) << endl;
        }
    }
    return 0;
}
