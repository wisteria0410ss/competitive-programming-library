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
<script type="text/javascript" src="../../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/library-checker/data_structure/point_set_range_composite.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#c4b8fe8a8231f4c5b6444b288e0b90cd">test/library-checker/data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/data_structure/point_set_range_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 15:35:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../../library/data_structure/segment-tree.hpp.html">data_structure/segment-tree.hpp</a>
* :question: <a href="../../../../library/math/modint.hpp.html">math/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/data_structure/point_set_range_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <bits/stdc++.h>
#line 3 "data_structure/segment-tree.hpp"

#pragma region segment-tree
template <typename Tp, typename Fp>
class segment_tree{
    Tp *tree;
    const size_t len;
    const Tp e;
    const Fp f;
public:
    segment_tree(size_t n, const Tp &id, Fp fn, const Tp *values=nullptr): len(n), e(id), f(fn){
        tree = new Tp[n<<1];
        for(size_t i=0; i<n; ++i) tree[n+i] = values ? values[i] : id;
        for(size_t i=n-1; i>0; --i) tree[i] = fn(tree[i<<1 | 0], tree[i<<1 | 1]);
    }
    void set(size_t pos, const Tp &val){
        tree[pos += len] = val;
        for(pos>>=1; pos>0; pos>>=1){
            tree[pos] = f(tree[pos<<1 | 0], tree[pos<<1 | 1]);
        }
    }
    void add(size_t pos, const Tp &val){
        pos += len;
        tree[pos] = f(val, tree[pos]);
        for(pos>>=1; pos>0; pos>>=1){
            tree[pos] = f(tree[pos<<1 | 0], tree[pos<<1 | 1]);
        }
    }
    Tp get(size_t left, size_t right){
        left += len; right += len;
        Tp lv = e, rv = e;
        while(left < right){
            if(left  & 1) lv = f(lv, tree[left ++]);
            if(right & 1) rv = f(tree[--right], rv);
            left >>= 1; right >>= 1;
        }
        return f(lv, rv);
    }
};
#pragma endregion
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
#line 6 "test/library-checker/data_structure/point_set_range_composite.test.cpp"
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

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

