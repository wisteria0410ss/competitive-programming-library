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
        else cout << uf.is_same(u, v)+1 << endl;
    }
    return 0;
}
