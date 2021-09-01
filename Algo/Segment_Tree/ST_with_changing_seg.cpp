#include <bits/stdc++.h>
 
using namespace std;
 
vector<long long> vec;
 
vector<long long> rsq;
 
vector<long long> sub;
 
void build(long long v, long long l, long long r){
    if(r - l == 1){
        rsq[v] = vec[l];
    }
    else{
        long long m = (l + r)/2;
        build(2 * v + 1 , l, m);
        build(2 * v + 2, m, r);
        rsq[v] = rsq[2 * v + 1] + rsq[2 * v + 2];
    }
}
 
void push(long long v, long long l, long long r){
    if(sub[v] != 0){
        sub[2 * v + 1] += sub[v];
        sub[2 * v + 2] += sub[v];
        rsq[2 * v + 1] += sub[v];
        rsq[2 * v + 2] += sub[v];
        sub[v] = 0;
    }
    return;
}
 
long long query(long long v, long long l, long long r, long long ql, long long qr){
    if(l >= qr || r <= ql){
        return 0;
    }
    if(ql <= l && r <= qr){
        return rsq[v];
    }
    push(v, l, r);
    long long m = (l + r)/2;
    return query(2 * v + 1, l, m, ql, qr) + query(2 * v + 2, m, r, ql, qr);
}
 
void add(long long v, long long l, long long r, long long ql, long long qr, long long x){
    if(l >= qr || r <= ql){
        return;
    }
    if(ql <= l && r <= qr){
        sub[v] += x;
        rsq[v] += x;
        return;
    }
    push(v, l, r);
    long long m = (l + r)/2;
    add(2 * v + 1, l, m, ql, qr, x);
    add(2 * v + 2, m, r, ql, qr, x);
    rsq[v] = rsq[2 * v + 1] + rsq[2 * v + 2];
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin >> n;
    vec.resize(n);
    long long p = 1;
    while(p < n){
        p *= 2;
    }
    for(auto& i : vec){
        cin >> i;
    }
    while(vec.size() != p){
        vec.push_back(0);
    }
    rsq.resize(2 * p - 1, 0);
    sub.resize(2 * p - 1, 0);
    build(0, 0, p);
    long long q;
    cin >> q;
    while(q--){
        char a;
        cin >> a;
        if(a == 'g'){
            long long b;
            cin >> b;
            b--;
            cout << query(0, 0, p, b, b + 1) << '\n';
        }
        else{
            long long l, r, x;
            cin >> l >> r >> x;
            l--;
            add(0, 0, p, l, r, x);
        }
    }
}