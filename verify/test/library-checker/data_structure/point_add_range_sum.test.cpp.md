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


# :heavy_check_mark: test/library-checker/data_structure/point_add_range_sum.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#c4b8fe8a8231f4c5b6444b288e0b90cd">test/library-checker/data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/data_structure/point_add_range_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 16:31:32+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../../library/data_structure/segment-tree.hpp.html">data_structure/segment-tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/data_structure/point_add_range_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

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
        for(pos>>=1; pos>0; pos>>=1) tree[pos] = f(tree[pos<<1 | 0], tree[pos<<1 | 1]);
    }
    void add(size_t pos, const Tp &val){
        pos += len;
        tree[pos] = f(val, tree[pos]);
        for(pos>>=1; pos>0; pos>>=1) tree[pos] = f(tree[pos<<1 | 0], tree[pos<<1 | 1]);
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
#line 5 "test/library-checker/data_structure/point_add_range_sum.test.cpp"

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

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

