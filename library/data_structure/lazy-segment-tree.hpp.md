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


# :heavy_check_mark: data_structure/lazy-segment-tree.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/lazy-segment-tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 16:10:07+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/data_structure/range_affine_range_sum.test.cpp.html">test/library-checker/data_structure/range_affine_range_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>

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
            if(r & 1){ --r; tree[r].operation = composition(f, tree[r].operation); }
            l >>= 1; r >>= 1;
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
            if(right & 1){ --right; evaluate(right); rval = merge(tree[right].value, rval); }
            left >>= 1; right >>= 1;
        }
        return merge(lval, rval);
    }
};
#pragma endregion

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/lazy-segment-tree.hpp"
#include <bits/stdc++.h>

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
            if(r & 1){ --r; tree[r].operation = composition(f, tree[r].operation); }
            l >>= 1; r >>= 1;
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
            if(right & 1){ --right; evaluate(right); rval = merge(tree[right].value, rval); }
            left >>= 1; right >>= 1;
        }
        return merge(lval, rval);
    }
};
#pragma endregion

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

