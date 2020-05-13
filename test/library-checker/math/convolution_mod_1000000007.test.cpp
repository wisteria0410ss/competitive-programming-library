#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <bits/stdc++.h>
#include "math/convolution-arbitary-mod.hpp"

constexpr uint32_t mod  = 1000000007;
using namespace std;
int main(){
    int n, m;
    static modint<mod> a[1<<20], b[1<<20], c[1<<20];
    cin >> n >> m;
    for(int i=0;i<n;++i) cin >> a[i];
    for(int i=0;i<m;++i) cin >> b[i];
    convolution<1<<20, mod>(a, b, c);
    for(int i=0;i<n+m-1;++i) cout << c[i] << " \n"[i==n+m-2];

    return 0;
}