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


# :warning: data_structure/partially-persistent-unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/partially-persistent-unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 22:24:15+09:00




## Required by

* :warning: <a href="../test/atcoder/code-thanks-festival-2017-open/h-union_sets.cpp.html">test/atcoder/code-thanks-festival-2017-open/h-union_sets.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bits/stdc++.h>

#pragma region partially-persistent-unionfind
class unionfind{
    int last;
    int *parent, *time;
    std::vector<std::pair<int, size_t>> *size;
    const size_t length;
public:
    unionfind(size_t n): last(0), length(n){
        parent = new int[n];
        time = new int[n];
        size = new std::vector<std::pair<int, size_t>>[n];
        for(size_t i=0;i<n;++i){
            parent[i] = 1;
            time[i] = INT32_MAX;
            size[i].emplace_back(0, 1);
        }
    }
    size_t root(size_t v, int t){
        if(time[v] > t) return v;
        else return root(parent[v], t);
    }
    bool is_same(size_t u, size_t v, int t=-1){
        if(t < 0) t = last;
        return root(u, t) == root(v, t);
    }
    int merge(size_t u, size_t v){
        int t = ++last;
        u = root(u, t);
        v = root(v, t);
        if(u == v) return t;
        if(parent[u] < parent[v]) std::swap(u, v);
        parent[u] += parent[v];
        size[u].emplace_back(t, parent[u]);
        parent[v] = u;
        time[v] = t;
        return t;
    }
    size_t count(size_t v, int t=-1){
        if(t < 0) t = last;
        v = root(v, t);
        return std::prev(std::lower_bound(size[v].begin(), size[v].end(), std::pair<int, size_t>{ t, length + 1 }))->second;
    }
};
#pragma endregion
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/partially-persistent-unionfind.hpp"
#include <bits/stdc++.h>

#pragma region partially-persistent-unionfind
class unionfind{
    int last;
    int *parent, *time;
    std::vector<std::pair<int, size_t>> *size;
    const size_t length;
public:
    unionfind(size_t n): last(0), length(n){
        parent = new int[n];
        time = new int[n];
        size = new std::vector<std::pair<int, size_t>>[n];
        for(size_t i=0;i<n;++i){
            parent[i] = 1;
            time[i] = INT32_MAX;
            size[i].emplace_back(0, 1);
        }
    }
    size_t root(size_t v, int t){
        if(time[v] > t) return v;
        else return root(parent[v], t);
    }
    bool is_same(size_t u, size_t v, int t=-1){
        if(t < 0) t = last;
        return root(u, t) == root(v, t);
    }
    int merge(size_t u, size_t v){
        int t = ++last;
        u = root(u, t);
        v = root(v, t);
        if(u == v) return t;
        if(parent[u] < parent[v]) std::swap(u, v);
        parent[u] += parent[v];
        size[u].emplace_back(t, parent[u]);
        parent[v] = u;
        time[v] = t;
        return t;
    }
    size_t count(size_t v, int t=-1){
        if(t < 0) t = last;
        v = root(v, t);
        return std::prev(std::lower_bound(size[v].begin(), size[v].end(), std::pair<int, size_t>{ t, length + 1 }))->second;
    }
};
#pragma endregion

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

