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
