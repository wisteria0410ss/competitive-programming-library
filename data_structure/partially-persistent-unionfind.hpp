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