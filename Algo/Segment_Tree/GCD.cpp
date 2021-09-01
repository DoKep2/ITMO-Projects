#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> vec;
 
vector<int> fun;
 
void build(int v, int l, int r){
    if(r - l == 1){
        fun[v] = vec[l];
    }
    else{
        int m = (l + r)/ 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        fun[v] = __gcd(fun[2 * v + 1], fun[2 * v + 2]   );
    }
}
 
int query(int v, int l, int r, int ql, int qr){
    if(ql >= r || qr <= l){
        return 0;
    }
    if(ql <= l && r <= qr){
        return fun[v];
    }
    int m = (l + r)/2;
    return __gcd(query(2 * v + 1, l, m, ql, qr), query(2 * v + 2, m, r, ql, qr));
}
 
int main()
{
 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vec.resize(n);
    int p = 1;
    while(p < n){
        p *= 2;
    }
    for(auto& i : vec){
        cin >> i;
    }
    while(vec.size() != p){
        vec.push_back(1);
    }
    fun.resize(2 * p - 1, 0);
    build(0, 0, p);
    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        l--;
        cout << query(0, 0, p, l, r) << ' ';
    }
 
}