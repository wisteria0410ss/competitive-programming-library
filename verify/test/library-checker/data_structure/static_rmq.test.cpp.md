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


# :heavy_check_mark: test/library-checker/data_structure/static_rmq.test.cpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#c4b8fe8a8231f4c5b6444b288e0b90cd">test/library-checker/data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/data_structure/static_rmq.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-07 17:25:09+09:00


* see: <a href="https://judge.yosupo.jp/problem/staticrmq">https://judge.yosupo.jp/problem/staticrmq</a>


## Depends on

* :heavy_check_mark: <a href="../../../../library/data_structure/disjoint-sparse-table.hpp.html">data_structure/disjoint-sparse-table.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
#include "data_structure/disjoint-sparse-table.hpp"

using namespace std;
int main(){
    int n, q;
    int64_t a[500000];
    cin >> n >> q;
    for(int i=0;i<n;++i) cin >> a[i];
    disjoint_sparse_table dst{n, a, [](auto x, auto y)->int64_t{ return min(x, y); }};

    while(q--){
        int l, r;
        cin >> l >> r;
        cout << dst.get(l, r) << endl;
    }
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/data_structure/static_rmq.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
#line 3 "data_structure/disjoint-sparse-table.hpp"

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
#line 5 "test/library-checker/data_structure/static_rmq.test.cpp"

using namespace std;
int main(){
    int n, q;
    int64_t a[500000];
    cin >> n >> q;
    for(int i=0;i<n;++i) cin >> a[i];
    disjoint_sparse_table dst{n, a, [](auto x, auto y)->int64_t{ return min(x, y); }};

    while(q--){
        int l, r;
        cin >> l >> r;
        cout << dst.get(l, r) << endl;
    }
    return 0;
}

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

