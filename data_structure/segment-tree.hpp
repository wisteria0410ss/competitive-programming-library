#pragma once
#include <bits/stdc++.h>

#pragma region segment-tree
template <typename Tp, typename Fp>
class segment_tree{
    Tp *tree;
    const size_t len;
    const Tp e;
    const Fp f;
public:
    segment_tree(size_t n, const Tp &id, Fp fn, const Tp *values=nullptr): len(n), e(id), f(fn){
        tree = new Tp[n<<1];
        for(size_t i=0; i<n; ++i) tree[n+i] = values ? values[i] : id;
        for(size_t i=n-1; i>0; --i) tree[i] = fn(tree[i<<1 | 0], tree[i<<1 | 1]);
    }
    void set(size_t pos, const Tp &val){
        tree[pos += len] = val;
        for(pos>>=1; pos>0; pos>>=1) tree[pos] = f(tree[pos<<1 | 0], tree[pos<<1 | 1]);
    }
    void add(size_t pos, const Tp &val){
        set(pos, f(val, tree[len + pos]));
    }
    Tp get(size_t left, size_t right){
        left += len; right += len;
        Tp lval = e, rval = e;
        while(left < right){
            if(left  & 1) lval = f(lval, tree[left ++]);
            if(right & 1) rval = f(tree[--right], rval);
            left >>= 1; right >>= 1;
        }
        return f(lval, rval);
    }
};
#pragma endregion
