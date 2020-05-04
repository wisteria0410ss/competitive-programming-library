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


# :x: test/atcoder/code-thanks-festival-2017-open/h-union_sets.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#1ad604b59ab5a4e81c3f55a21b409f92">test/atcoder/code-thanks-festival-2017-open</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/atcoder/code-thanks-festival-2017-open/h-union_sets.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 22:24:15+09:00




## Depends on

* :x: <a href="../../../../library/data_structure/partially-persistent-unionfind.hpp.html">data_structure/partially-persistent-unionfind.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #define PROBLEM "https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h"

#include <bits/stdc++.h>
#include "data_structure/partially-persistent-unionfind.hpp"

using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    unionfind uf{n+1};
    for(int i=0;i<m;++i){
        int a, b;
        cin >> a >> b;
        uf.merge(a, b);
    }
    int q;
    cin >> q;
    while(q--){
        int x, y;
        cin >> x >> y;
        if(!uf.is_same(x, y)){ cout << -1 << endl; continue; }
        int ok = m, ng = 0;
        while(ok - ng > 1){
            int mid = (ok + ng) / 2;
            if(uf.is_same(x, y, mid)) ok = mid;
            else ng = mid;
        }
        cout << ok << endl;
    }

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/atcoder/code-thanks-festival-2017-open/h-union_sets.test.cpp"
// #define PROBLEM "https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h"

#include <bits/stdc++.h>
#line 3 "data_structure/partially-persistent-unionfind.hpp"

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
#line 5 "test/atcoder/code-thanks-festival-2017-open/h-union_sets.test.cpp"

using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    unionfind uf{n+1};
    for(int i=0;i<m;++i){
        int a, b;
        cin >> a >> b;
        uf.merge(a, b);
    }
    int q;
    cin >> q;
    while(q--){
        int x, y;
        cin >> x >> y;
        if(!uf.is_same(x, y)){ cout << -1 << endl; continue; }
        int ok = m, ng = 0;
        while(ok - ng > 1){
            int mid = (ok + ng) / 2;
            if(uf.is_same(x, y, mid)) ok = mid;
            else ng = mid;
        }
        cout << ok << endl;
    }

    return 0;
}

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

