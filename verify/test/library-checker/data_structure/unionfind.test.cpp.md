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


# :heavy_check_mark: test/library-checker/data_structure/unionfind.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#c4b8fe8a8231f4c5b6444b288e0b90cd">test/library-checker/data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/data_structure/unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-02 16:40:09+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../../../library/data_structure/unionfind.hpp.html">data_structure/unionfind.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
#include "data_structure/unionfind.hpp"

using namespace std;
int main(){
    int n, q;
    cin >> n >> q;
    unionfind uf{n};
    while(q--){
        int t, u, v;
        cin >> t >> u >> v;
        if(t == 0) uf.merge(u, v);
        else cout << uf.is_same(u, v) << endl;
    }
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/data_structure/unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
#line 3 "data_structure/unionfind.hpp"

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
#line 5 "test/library-checker/data_structure/unionfind.test.cpp"

using namespace std;
int main(){
    int n, q;
    cin >> n >> q;
    unionfind uf{n};
    while(q--){
        int t, u, v;
        cin >> t >> u >> v;
        if(t == 0) uf.merge(u, v);
        else cout << uf.is_same(u, v) << endl;
    }
    return 0;
}

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

