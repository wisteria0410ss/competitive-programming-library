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


# :x: test/library-checker/data_structure/range_affine_range_sum.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#c4b8fe8a8231f4c5b6444b288e0b90cd">test/library-checker/data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/data_structure/range_affine_range_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 16:02:09+09:00


* see: <a href=""></a>


## Depends on

* :x: <a href="../../../../library/data_structure/lazy-segment-tree.hpp.html">data_structure/lazy-segment-tree.hpp</a>
* :question: <a href="../../../../library/math/modint.hpp.html">math/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/data_structure/range_affine_range_sum.test.cpp"
#define PROBLEM ""

#include <bits/stdc++.h>
#line 3 "data_structure/lazy-segment-tree.hpp"

#pragma region lazy-segment-tree
template <typename Tp, typename Op>
class segment_tree{
    struct node{
        Tp value;
        Op operation;
        size_t width;
    } *tree;
    const size_t length;
    const Tp vid;
    const Op oid;
    Tp (*const merge)(const Tp &lhs, const Tp &rhs);
    Op (*const composition)(const Op &lhs, const Op &rhs);
    Tp (*const action)(const Op &f, const Tp &x, size_t width);

    void evaluate(size_t pos){
        if(tree[pos].operation == oid) return;
        if(pos < length){
            tree[pos<<1 | 0].operation = composition(tree[pos].operation, tree[pos<<1 | 0].operation);
            tree[pos<<1 | 1].operation = composition(tree[pos].operation, tree[pos<<1 | 1].operation);
        }
        tree[pos].value = action(tree[pos].operation, tree[pos].value, tree[pos].width);
        tree[pos].operation = oid;
    }
    void propagate(size_t left, size_t right){
        for(int i = sizeof(unsigned int) * CHAR_BIT - __builtin_clz(left ) - 1; i > 0; --i) evaluate(left  >> i);
        for(int i = sizeof(unsigned int) * CHAR_BIT - __builtin_clz(right) - 1; i > 0; --i) evaluate(right >> i);
    }
    void update(size_t left, size_t right){
        for(left  >>= __builtin_ctz(left ) + 1; left ; left  >>= 1){
            evaluate(left <<1 | 0);
            evaluate(left <<1 | 1);
            tree[left ].value = merge(tree[left <<1 | 0].value, tree[left <<1 | 1].value);
        }
        for(right >>= __builtin_ctz(right) + 1; right; right >>= 1){
            evaluate(right <<1 | 0);
            evaluate(right <<1 | 1);
            tree[right].value = merge(tree[right<<1 | 0].value, tree[right<<1 | 1].value);
        }
    }
public:
    segment_tree(size_t n,
        Tp e, Tp(*const fold)(const Tp&, const Tp&),
        Op id, Op (*const compose)(const Op&, const Op&),
        Tp (*const apply)(const Op&, const Tp&, size_t))
    : length(n), vid(e), oid(id), merge(fold), composition(compose), action(apply){
        tree = new node[n<<1];
        for(size_t i = 1; i < (n<<1); ++i) tree[i] = { e, id, 1 };
        for(size_t i = n - 1; i > 0; --i) tree[i].width = tree[i<<1 | 0].width + tree[i<<1 | 1].width;
    }
    void set(size_t left, size_t right, Op f){
        if(left >= right) return;
        size_t l, r;
        l = left  = left  + length;
        r = right = right + length;
        propagate(left, right);
        while(l < r){
            if(l & 1){ tree[l].operation = composition(f, tree[l].operation); ++l; }
            l >>= 1;
            if(r & 1){ --r; tree[r].operation = composition(f, tree[r].operation); }
            r >>= 1;
        }
        update(left, right);
    }
    void init(Tp *val){
        for(size_t i = 0; i < length; ++i) tree[length + i].value = val[i];
        for(size_t i = length - 1; i > 0; --i) tree[i].value = merge(tree[i<<1 | 0].value, tree[i<<1 | 1].value);
    }
    Tp get(size_t left, size_t right){        
        if(left >= right) return vid;
        left  += length;
        right += length;
        propagate(left, right);
        Tp lval = vid, rval = vid;
        while(left < right){
            if(left  & 1){ evaluate(left ); lval = merge(lval, tree[left ].value); ++left ; }
            left >>= 1;
            if(right & 1){ --right; evaluate(right); rval = merge(tree[right].value, rval); }
            right >>= 1;
        }
        return merge(lval, rval);
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
#line 6 "test/library-checker/data_structure/range_affine_range_sum.test.cpp"
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

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

