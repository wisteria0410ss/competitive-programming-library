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


# :x: data_structure/unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-02 16:40:09+09:00




## Verified with

* :x: <a href="../../verify/test/library-checker/data_structure/unionfind.test.cpp.html">test/library-checker/data_structure/unionfind.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>

#pragma region unionfind
class unionfind{
    int *tree;
    size_t length;
    size_t root(size_t v){
        if(tree[v] < 0) return v;
        else return tree[v] = root(tree[v]);
    }
public:
    unionfind(size_t n): length(n){
        tree = new int[n];
        for(size_t i=0;i<n;++i) tree[i] = -1;
    }
    size_t count(size_t v){
        return -tree[root(v)];
    }
    bool is_same(size_t u, size_t v){
        return root(u) == root(v);
    }
    bool merge(size_t u, size_t v){
        u = root(u); v = root(v);
        if(u == v) return false;
        if(u > v) std::swap(u, v);
        tree[u] += tree[v];
        tree[v] = u;
        return true;
    }
};
#pragma endregion

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/unionfind.hpp"
#include <bits/stdc++.h>

#pragma region unionfind
class unionfind{
    int *tree;
    size_t length;
    size_t root(size_t v){
        if(tree[v] < 0) return v;
        else return tree[v] = root(tree[v]);
    }
public:
    unionfind(size_t n): length(n){
        tree = new int[n];
        for(size_t i=0;i<n;++i) tree[i] = -1;
    }
    size_t count(size_t v){
        return -tree[root(v)];
    }
    bool is_same(size_t u, size_t v){
        return root(u) == root(v);
    }
    bool merge(size_t u, size_t v){
        u = root(u); v = root(v);
        if(u == v) return false;
        if(u > v) std::swap(u, v);
        tree[u] += tree[v];
        tree[v] = u;
        return true;
    }
};
#pragma endregion

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

