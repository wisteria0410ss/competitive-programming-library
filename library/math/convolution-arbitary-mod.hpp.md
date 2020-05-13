---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: math/convolution-arbitary-mod.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/convolution-arbitary-mod.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-14 00:26:26+09:00




## Depends on

* :heavy_check_mark: <a href="convolution.hpp.html">math/convolution.hpp</a>
* :heavy_check_mark: <a href="modint.hpp.html">math/modint.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/math/convolution_mod_1000000007.test.cpp.html">test/library-checker/math/convolution_mod_1000000007.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>
#include "math/convolution.hpp"

#pragma region convolution-arbitary-mod
constexpr uint64_t add_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret = 0;
    if(__builtin_uaddll_overflow(lhs, rhs, &ret)) ret += 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
constexpr uint64_t mul_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret = 0;
    __uint128_t mul = lhs;
    mul *= rhs;
    lhs = mul >> 64;
    rhs = mul;
    if(__builtin_uaddll_overflow(rhs, (lhs & 0xffffffff) * 0xffffffff, &ret)) ret += 0xffffffff;
    if(__builtin_usubll_overflow(ret, lhs >> 32, &ret)) ret -= 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
constexpr uint64_t pow_f01(uint64_t x, uint64_t y){
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
    constexpr uint64_t ninv = pow_f01(n, mod-2);
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "math/convolution-arbitary-mod.hpp"
#include <bits/stdc++.h>
#line 3 "math/modint.hpp"

#pragma region modint
template <uint32_t mod>
class modint{
    uint64_t value;
public:
    constexpr modint(const int64_t x=0) noexcept: value(x % mod + (x < 0 ? mod : 0)){ }
    constexpr explicit operator uint64_t() const noexcept{ return value; }
    constexpr modint inverse() const noexcept{ return pow(*this, mod-2); }
    constexpr bool operator==(const modint &rhs) const noexcept{ return value == rhs.value; }
    constexpr bool operator!=(const modint &rhs) const noexcept{ return value != rhs.value; }
    constexpr modint operator+() const noexcept{ return modint(*this); }
    constexpr modint operator-() const noexcept{ return modint(mod - value); }
    constexpr modint operator+(const modint &rhs) const noexcept{ return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept{ return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept{ return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept{ return modint(*this) /= rhs; }
    constexpr modint &operator+=(const modint &rhs) noexcept{
        if((value += rhs.value) >= mod) value -= mod;
        return *this;
    }
    constexpr modint &operator-=(const modint &rhs) noexcept{ return *this += mod - rhs.value; }
    constexpr modint &operator*=(const modint &rhs) noexcept{
        if((value *= rhs.value) >= mod) value %= mod;
        return *this;
    }
    constexpr modint &operator/=(const modint &rhs) noexcept{ return *this *= rhs.inverse(); }
    constexpr modint operator++(int) noexcept{
        modint ret(*this);
        if((++value) >= mod) value -= mod;
        return ret;
    }
    constexpr modint operator--(int) noexcept{
        modint ret(*this);
        if((value += mod - 1) >= mod) value -= mod;
        return ret;
    }
    constexpr modint &operator++() noexcept{ return *this += 1; }
    constexpr modint &operator--() noexcept{ return *this -= 1; }
    friend std::ostream &operator<<(std::ostream &os, const modint<mod> &x){ return os << x.value; }
    friend std::istream &operator>>(std::istream &is, modint<mod> &x){
        int64_t i;
        is >> i;
        x = modint<mod>(i);
        return is;
    }
    friend constexpr modint<mod> pow(const modint<mod> &x, uint64_t y){
        modint<mod> ret{1}, m{x};
        while(y > 0){
            if(y & 1) ret *= m;
            m *= m;
            y >>= 1;
        }
        return ret;
    }
};
#pragma endregion
#line 4 "math/convolution.hpp"

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
#line 4 "math/convolution-arbitary-mod.hpp"

#pragma region convolution-arbitary-mod
constexpr uint64_t add_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret = 0;
    if(__builtin_uaddll_overflow(lhs, rhs, &ret)) ret += 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
constexpr uint64_t mul_f01(uint64_t lhs, uint64_t rhs){
    constexpr uint64_t mod = 0xffffffff00000001;
    unsigned long long ret = 0;
    __uint128_t mul = lhs;
    mul *= rhs;
    lhs = mul >> 64;
    rhs = mul;
    if(__builtin_uaddll_overflow(rhs, (lhs & 0xffffffff) * 0xffffffff, &ret)) ret += 0xffffffff;
    if(__builtin_usubll_overflow(ret, lhs >> 32, &ret)) ret -= 0xffffffff;
    return ret < mod ? ret : ret - mod;
}
constexpr uint64_t pow_f01(uint64_t x, uint64_t y){
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
    constexpr uint64_t ninv = pow_f01(n, mod-2);
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

