#include <bits/stdc++.h>

using namespace std;

const long long MOD = 50000;

const long long p = 43;

typedef struct tab{
    string in;
    string key;
    string p;
    string n;
    int num_pr;
    int num_next;
} tab;

vector<vector<tab> > h;

typedef struct l{
    int num;
    string in;
    string key;
}l;

l last = {-1, "1", "1"};

int find_key(int n, string input){
    if(n < 0){
        return -1;
    }
    for(int i = 0; i < h[n].size(); i++){
        if(h[n][i].in == input){
            return i;
        }
    }
    return -1;
}

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
    int a = find_key(n, input);
    if(a != -1){
        h[n][a].key = key;
        return;
    }
    h[n].push_back({input, key, last.in, "1", last.num, -1});
    if(last.num != -1){
        int a = find_key(last.num, last.in);
        if(a != -1){
        h[last.num][a].n = input;
        h[last.num][a].num_next = n;
        }
    }
    last.key = key;
    last.in = input;
    last.num = n;
}

void del(int n, string input){
    int a = find_key(n, input);
    if(a == -1){
        return;
    }
    if(last.num == n && last.in == input){
        last.num = h[n][a].num_pr;
        last.in = h[n][a].p;
        int nn = h[n][a].num_pr;
        if(nn == -1){
            last.key = "1";
        }
        else{
            int b = find_key(nn, h[n][a].p);
            last.key = h[nn][b].key;
        }
    }
    if(h[n][a].p != "1"){
        int nn = h[n][a].num_pr;
        if(nn != -1){
            int b = find_key(nn, h[n][a].p);
            h[nn][b].n = h[n][a].n;
            h[nn][b].num_next = h[n][a].num_next;
        }
    }
    if(h[n][a].n != "1"){
        int nn = h[n][a].num_next;
        if(nn != -1){
            int b = find_key(nn, h[n][a].n);
            h[nn][b].p = h[n][a].p;
            h[nn][b].num_pr = h[n][a].num_pr;
        }
    }
    for(int i = 0; i < h[n].size(); i++){
        if(h[n][i].in == input){
            h[n].erase(h[n].begin() + i, h[n].begin() + i + 1);
            break;
        }
    }
}

int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
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
            del(nn, n);
        }
        else if(s == "get"){
            int a = find_key(nn, n);
            if(a == -1){
                cout << "none\n";
            }
            else{
                cout << h[nn][a].key << '\n';
            }
        }
        else if(s == "prev"){
            int a = find_key(nn, n);
            if(a == -1){
                cout << "none\n";
            }
            else{
                string p = h[nn][a].p;
                if(p == "1"){
                    cout << "none\n";
                    continue;
                }
                int num = h[nn][a].num_pr;
                int b = find_key(num, p);
                if(b == -1){
                    cout << "none\n";
                }
                else{
                    cout << h[num][b].key << '\n';
                }
            }
        }
        else{
            int a = find_key(nn, n);
            if(a == -1){
                cout << "none\n";
            }
            else{
                string p = h[nn][a].n;
                if(p == "1"){
                    cout << "none\n";
                    continue;
                }
                int num = h[nn][a].num_next;
                int b = find_key(num, p);
                if(b == -1){
                    cout << "none\n";
                }
                else{
                    cout << h[num][b].key << '\n';
                }
            }
        }
    }
}
