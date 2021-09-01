#include <bits/stdc++.h>

using namespace std;

const long long MOD = 50000;

const long long p = 43;

vector<vector<pair<string, string> > > h;

long long hash_(string a){
    long long sz = a.size();
    vector<long long> hs(sz);
    hs[0] = a[0] - 'a';
    for(long long i = 1; i < sz; i++){
        hs[i] = (hs[i - 1] * p + a[i] - '0') % MOD;
    }
    return (hs[sz - 1] + MOD)%MOD;
}

void put(long long n, string input, string key){
    for(long long i = 0; i < h[n].size(); i++){
        if(h[n][i].first == input){
            h[n][i].second = key;
            return;
        }
    }
    h[n].push_back({input, key});
}

string get_(long long n, string input){
    for(long long i = 0; i < h[n].size(); i++){
        if(h[n][i].first == input){
            return h[n][i].second;
        }
    }
    return "none";
}

void delete_hash(long long n, string input){
    for(long long i = 0; i < h[n].size(); i++){
        if(h[n][i].first == input){
            h[n].erase(h[n].begin() + i, h[n].begin() + i + 1);
        }
    }
}


int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    string s;
    h.resize(MOD);
    while(cin >> s){
        string n;
        cin >> n;
        int nn = hash_(n);
        if(s == "put"){
            string t;
            cin >> t;
            put(nn, n, t);
        }
        else if(s == "delete"){
            delete_hash(nn, n);
        }
        else{
            cout << get_(nn, n) << '\n';
        }
    }
}
