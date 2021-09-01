#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = -1e9 - 1;
 
vector<long long> vec;
 
vector<long long> rmq;
 
void build(int v, int l, int r){
    if(r - l == 1){
        rmq[v] = vec[l];
    }
    else{
        int m = (l + r)/2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        rmq[v] = max(rmq[2 * v + 1], rmq[2 * v + 2]);
    }
}
 
 
long long query(int v, int l, int r, int ql, int qr){
    if(l >= qr || r - 1 < ql){
        return INF;
    }
    ql = max(ql, l);
    qr = min(qr, r);
    if(ql == l && qr == r){
        return rmq[v];
    }
    else{
        int m = (l + r)/2;
        return max(query(2 * v + 1, l, m, ql, qr), query(2 * v + 2, m, r, ql, qr));
    }
}
 
void change(int v, int l, int r, int pos, int new_){
    if(l > pos || r - 1 < pos){
        return;
    }
    if(r - l == 1){
        rmq[v] = new_;
    }
    else{
        int m = (l + r)/2;
        if(pos < m){
            change(2 * v + 1, l, m, pos, new_);
        }
        else{
            change(2 * v + 2, m, r, pos, new_);
        }
        rmq[v] = max(rmq[2 * v + 1], rmq[2 * v + 2]);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vec.resize(n);
    for(auto& i : vec){
        cin >> i;
    }
    int p = 1;
    while(p < n){
        p *= 2;
    }
    while(vec.size() != p){
        vec.push_back(INF);
    }
    rmq.resize(2 * p - 1, INF);
    build(0, 0, p);
    int q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c == 'm'){
            int a, b;
            cin >> a >> b;
            a--;
            cout << query(0, 0, p, a, b) << ' ';
        }
        else{
            int a, b;
            cin >> a >> b;
            a--;
            change(0, 0, p, a, b);
        }
    }
}