#pragma once
#include <bits/stdc++.h>
#include "math/modint.hpp"

#pragma region convolution
template <size_t n, uint32_t mod, uint32_t root>
void ntt(const modint<mod> *input, modint<mod> *output, bool rev=false){
    static_assert((n & n-1) == 0 && (mod - 1) % n == 0);
    constexpr int st = __builtin_ctzll(n);
    constexpr modint<mod> ninv = modint<mod>{n}.inverse();
    static std::vector<modint<mod>> omega = [](){
        std::vector<modint<mod>> ret;
        ret.resize(n+1);
        ret[0] = 1; if(n == 1) return ret;
        ret[1] = pow(modint<mod>{root}, (mod - 1) / n);
        for(size_t i=2;i<=n;++i) ret[i] = ret[i-1] * ret[1];
        return ret;
    }();

    for(size_t i=0;i<n;++i) output[i] = rev ? input[i] * ninv : input[i];
    for(int s = (rev ? st-1 : 0); rev ? s>=0 : s<st; rev ? --s : ++s){
        const int h = n >> s+1, l = n >> s;
        for(int b=0;b<(1<<s);++b){
            for(int i=0;i<h;++i){
                const modint<mod> x = output[l*b+i], y = rev ? output[l*b+h+i] * omega[n - (i << s)] : output[l*b+h+i];
                output[l*b  +i] = x + y;
                output[l*b+h+i] = rev ? x - y : (x - y) * omega[i << s];
            }
        }
    }
};

template <size_t n, uint32_t mod, uint32_t root>
void convolution(const modint<mod> *lhs, const modint<mod> *rhs, modint<mod> *output){
    static modint<mod> w[n];
    ntt<n, mod, root>(lhs, output);
    ntt<n, mod, root>(rhs, w);
    for(size_t i=0;i<n;++i) w[i] *= output[i];
    ntt<n, mod, root>(w, output, true);
}
#pragma endregion