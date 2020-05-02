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


# :heavy_check_mark: data_structure/disjoint-sparse-table.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/disjoint-sparse-table.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-02 20:33:57+09:00




## Required by

* :warning: <a href="../test/library-checker/data_structure/static_rmq.cpp.html">test/library-checker/data_structure/static_rmq.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/data_structure/static_range_sum.test.cpp.html">test/library-checker/data_structure/static_range_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>

#pragma region disjoint-sparse-table
template <typename Tp, typename Fp>
class disjoint_sparse_table{
    Tp **table;
    Fp func;
    size_t length, lg;
public:
    disjoint_sparse_table(size_t n, Tp *values, Fp f): length(n), func(f){
        lg = CHAR_BIT * sizeof(int) - __builtin_clz(std::max((size_t)1, n-1));
        table  = new Tp*[lg];
        *table = new Tp[n * lg];
        for(int i=1;i<lg;++i) table[i] = *table + n * i;
        for(int i=0;i<n;++i) table[0][i] = values[i];
        for(int s=1;s<lg;++s){
            size_t w = 1<<s;
            for(int i=0;i<n;i+=w<<1){
                size_t l = std::min(i + w, n) - 1, r = i + w;
                table[s][l] = values[l];
                for(int j=l-1;j>=i;--j) table[s][j] = f(values[j], table[s][j+1]);
                if(r >= n) continue;
                table[s][r] = values[r];
                for(int j=r+1;j<r+w && j<n;++j) table[s][j] = f(table[s][j-1], values[j]);
            }
        }
    }
    Tp get(size_t left, size_t right, Tp id=Tp{}){
        if(left >= right || right > length) return id;
        if(left + 1 == right) return table[0][left];
        size_t s = CHAR_BIT * sizeof(int) - __builtin_clz(left ^ --right) - 1;
        return func(table[s][left], table[s][right]);
    }
};
#pragma endregion

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/disjoint-sparse-table.hpp"
#include <bits/stdc++.h>

#pragma region disjoint-sparse-table
template <typename Tp, typename Fp>
class disjoint_sparse_table{
    Tp **table;
    Fp func;
    size_t length, lg;
public:
    disjoint_sparse_table(size_t n, Tp *values, Fp f): length(n), func(f){
        lg = CHAR_BIT * sizeof(int) - __builtin_clz(std::max((size_t)1, n-1));
        table  = new Tp*[lg];
        *table = new Tp[n * lg];
        for(int i=1;i<lg;++i) table[i] = *table + n * i;
        for(int i=0;i<n;++i) table[0][i] = values[i];
        for(int s=1;s<lg;++s){
            size_t w = 1<<s;
            for(int i=0;i<n;i+=w<<1){
                size_t l = std::min(i + w, n) - 1, r = i + w;
                table[s][l] = values[l];
                for(int j=l-1;j>=i;--j) table[s][j] = f(values[j], table[s][j+1]);
                if(r >= n) continue;
                table[s][r] = values[r];
                for(int j=r+1;j<r+w && j<n;++j) table[s][j] = f(table[s][j-1], values[j]);
            }
        }
    }
    Tp get(size_t left, size_t right, Tp id=Tp{}){
        if(left >= right || right > length) return id;
        if(left + 1 == right) return table[0][left];
        size_t s = CHAR_BIT * sizeof(int) - __builtin_clz(left ^ --right) - 1;
        return func(table[s][left], table[s][right]);
    }
};
#pragma endregion

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

