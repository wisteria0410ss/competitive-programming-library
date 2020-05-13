#pragma once
#include <bits/stdc++.h>
#include "math/convolution.hpp"

#pragma region convolution-arbitary-mod
uint64_t add_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret;
    if(__builtin_uaddll_overflow(lhs, rhs, &ret)) ret += 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
uint64_t mul_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret;
    asm("movq %2, %%rax\n"
        "movq %3, %%rdx\n"
        "mulq %%rdx\n"
        "movq %%rdx, %0\n"
        "movq %%rax, %1\n"
        : "=r"(lhs), "=r"(rhs)
        : "r"(lhs), "r"(rhs)
        : "%rax", "%rdx");
    if(__builtin_uaddll_overflow(rhs, (lhs & 0xffffffff) * 0xffffffff, &ret)) ret += 0xffffffff;
    if(__builtin_usubll_overflow(ret, lhs >> 32, &ret)) ret -= 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
uint64_t pow_f01(uint64_t x, uint64_t y){
    uint64_t ret = 1, m = x;
    while(y > 0){
        if(y & 1) ret = mul_f01(ret, m);
        m = mul_f01(m, m);
        y >>= 1;
    }
    return ret;
}

template <size_t n>
void ntt_bitrev_f01(const uint64_t *input, uint64_t *output, bool rev=false){
    constexpr uint64_t mod  = 0xffffffff00000001;
    constexpr uint64_t root = 7;

    static_assert((n & n-1) == 0 && (mod - 1) % n == 0);
    constexpr int st = __builtin_ctzll(n);
    const uint64_t ninv = pow_f01(n, mod-2);
    static std::vector<uint64_t> omega = [](){
        std::vector<uint64_t> ret;
        ret.resize(n+1);
        ret[0] = 1; if(n == 1) return ret;
        ret[1] = pow_f01(root, (mod - 1) / n);
        for(size_t i=2;i<=n;++i) ret[i] = mul_f01(ret[i-1], ret[1]);
        return ret;
    }();

    for(size_t i=0;i<n;++i) output[i] = rev ? mul_f01(input[i], ninv) : input[i];
    for(int s = (rev ? st-1 : 0); rev ? s>=0 : s<st; rev ? --s : ++s){
        const int h = n >> s+1, l = n >> s;
        for(int b=0;b<(1<<s);++b){
            for(int i=0;i<h;++i){
                const uint64_t x = output[l*b+i], y = rev ? mul_f01(output[l*b+h+i], omega[n - (i << s)]) : output[l*b+h+i];
                output[l*b  +i] = add_f01(x, y);
                output[l*b+h+i] = rev ? add_f01(x, mod - y) : mul_f01(add_f01(x, mod - y), omega[i << s]);
            }
        }
    }
}

template <size_t n>
void convolution_f01(const uint64_t *lhs, const uint64_t *rhs, uint64_t *output){
    static uint64_t w[n];
    ntt_bitrev_f01<n>(lhs, output);
    ntt_bitrev_f01<n>(rhs, w);
    for(size_t i=0;i<n;++i) w[i] = mul_f01(w[i], output[i]);
    ntt_bitrev_f01<n>(w, output, true);
}

template <size_t n, uint32_t mod>
void convolution(const modint<mod> *lhs, const modint<mod> *rhs, modint<mod> *output){
    constexpr uint64_t modf01 = 0xffffffff00000001, modc01 = 0xc0000001;
    constexpr uint32_t rootc01= 5;
    static modint<modc01> mx[n], my[n], mz[n];
    static uint64_t ux[n], uy[n], uz[n];
    for(size_t i=0;i<n;++i){
        mx[i] = ux[i] = (uint64_t)lhs[i];
        my[i] = uy[i] = (uint64_t)rhs[i];
    }
    convolution<n, modc01, rootc01>(mx, my, mz);
    convolution_f01<n>(ux, uy, uz);
    for(size_t i=0;i<n;++i){
        int64_t k = (uint64_t)((mz[i] - uz[i] % modc01) / (modf01 % modc01));
        output[i] = modint<mod>{k} * modint<mod>{modf01 % mod} + modint<mod>{uz[i] % mod};
    }
}
#pragma endregion