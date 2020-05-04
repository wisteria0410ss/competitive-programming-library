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


# :heavy_check_mark: data_structure/segment-tree.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment-tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 16:31:32+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/data_structure/point_add_range_sum.test.cpp.html">test/library-checker/data_structure/point_add_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/data_structure/point_set_range_composite.test.cpp.html">test/library-checker/data_structure/point_set_range_composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/segment-tree.hpp"
#include <bits/stdc++.h>

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

