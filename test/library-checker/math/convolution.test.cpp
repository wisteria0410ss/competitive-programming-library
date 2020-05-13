#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <bits/stdc++.h>
#include "math/convolution.hpp"

constexpr uint32_t mod  = 998244353;
constexpr uint32_t root = 3;
using namespace std;
int main(){
    int n, m;
    static modint<mod> a[1<<20], b[1<<20], c[1<<20];
    cin >> n >> m;
    for(int i=0;i<n;++i) cin >> a[i];
    for(int i=0;i<m;++i) cin >> b[i];
    convolution<1<<20, mod, root>(a, b, c);
    for(int i=0;i<n+m-1;++i) cout << c[i] << " \n"[i==n+m-2];

    return 0;
}