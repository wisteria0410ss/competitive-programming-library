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
