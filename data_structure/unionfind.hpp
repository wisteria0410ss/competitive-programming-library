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
