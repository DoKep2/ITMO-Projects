#include <bits/stdc++.h>

using namespace std;

const long long MOD = 50000;

const long long p = 43;

vector<vector<long long> > h;

long long hash_(string a){
    long long sz = a.size();
    vector<long long> hs(sz);
    hs[0] = a[0] - 'a';
    for(long long i = 1; i < sz; i++){
        hs[i] = (hs[i - 1] * p + a[i] - '0') % MOD;
    }
    return (hs[sz - 1] + MOD)%MOD;
}

bool find_hash(long long n, long long key){
    for(long long i = 0; i < h[n].size(); i++){
        if(h[n][i] == key){
            return 1;
        }
    }
    return 0;
}

void delete_hash(long long n, long long key){
    for(long long i = 0; i < h[n].size(); i++){
        if(h[n][i] == key){
            h[n].erase(h[n].begin() + i, h[n].begin() + i + 1);
        }
    }
}

int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    string s;
    h.resize(MOD);
    while(cin >> s){
        string n;
        cin >> n;
        int num = 0;
        for(int i = 0; i < n.size(); i++){
            num *= 10;
            num += n[i] - '0';
        }
        string a = n;
        int nn = hash_(n);
        if(s == "insert"){
            if(!find_hash(nn, num)){
                h[nn].push_back(num);
            }
        }
        else if(s == "delete"){
            delete_hash(nn, num);
        }
        else{
            if(!find_hash(nn, num)){
                cout << "false\n";
            }
            else{
                cout << "true\n";
            }
        }
    }
}
