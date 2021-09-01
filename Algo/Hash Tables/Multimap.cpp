#include <bits/stdc++.h>

#pragma GCC optimize("O3,Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx2,tune=native")

using namespace std;


int main(){
/*put c 1
put a 2
put b 3
put a 4
put b 5
prev a
next a
prev b
next b
next c*/
ios_base::sync_with_stdio(0);
cin.tie(0); cout.tie(0);
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    string s;
    vector<pair<string, pair<int, string> > > nums;
    vector<pair<string, pair<int, string> > > newvec;
    int c = 0;
    while(cin >> s){
        string a;
        cin >> a;
        string kek = "-1";
        if(s == "put" || s == "delete"){
            string k;
            cin >> k;
            kek = k;
        }
        newvec.push_back({s, {-1, kek}});
        nums.push_back({a, {c, kek}});
        c++;
    }

    sort(nums.begin(), nums.end());
    int cnt = 0;
    for(int i = 0; i < nums.size(); i++){
        while(i + 1 < nums.size() && nums[i].first == nums[i + 1].first){
            newvec[nums[i].second.first].second.first = cnt;
///            acc[cnt] = nums[i].first;
            i++;
        }
        newvec[nums[i].second.first].second.first = cnt;
        cnt++;
    }/*
    for(auto& i : newvec){
        cout << i.first << ' ' << i.second.first << ' ' << i.second.second << '\n';
    }
    return 0;*/
    vector<vector<pair<string, int> > > dcp(cnt);
    for(int i = 0; i < c; i++){
            if(newvec[i].second.second != "-1")
        dcp[newvec[i].second.first].push_back({newvec[i].second.second, i});
    }
    vector<pair<string, pair<int, int> > > supervector(c);
    for(int i = 0; i < c; i++){
        supervector[i].first = newvec[i].first;
        supervector[i].second.first = newvec[i].second.first;
    }
    vector<int> size_(cnt);
    vector<vector<string> > acc1(cnt);
    vector<int> pos(c);
    for(int i = 0; i < dcp.size(); i++){
        sort(dcp[i].begin(), dcp[i].end());
        int cc = 0;
        for(int j = 0; j < dcp[i].size(); j++){
            while(j + 1 < dcp[i].size() && dcp[i][j].first == dcp[i][j + 1].first){
                supervector[dcp[i][j].second].second.second = cc;
                j++;
            }
            supervector[dcp[i][j].second].second.second = cc;
            acc1[i].push_back(dcp[i][j].first);
            size_[i]++;
            cc++;
        }
    }
/*
    for(auto& i : supervector){
        cout << i.first << ' ' << i.second.first << ' ' << i.second.second << '\n';
    }
    return 0;*/
/*
    for(int i = 0; i < c; i++){
        cout << supervector[i].first << ' ' << acc[newvec[i].second.first] << ' ' << acc1[i][0] << '\n';
    }*/
    vector<vector<bool> > have(cnt);
    vector<vector<int> > tmp(cnt);
    for(int i = 0; i < cnt; i++){
        tmp[i].resize(size_[i], -1);
        have[i].resize(size_[i], 0);
    }
    vector<int> sz(cnt);
    vector<vector<int> > pos1(cnt);
    for(int i = 0; i < c; i++){
            int a = supervector[i].second.first;
            int b = supervector[i].second.second;
        if(supervector[i].first == "put"){
            if(tmp[a][b] == -1){
                    sz[a]++;
                    if(!have[a][b]){
                    pos1[a].push_back(b);
                    have[a][b] = 1;
                    }
            }
            tmp[a][b] = 1;
        }
        else if(supervector[i].first == "delete"){
            if(tmp[a][b] == 1){
                    sz[a]--;
            }
            tmp[a][b] = -1;
        }
        else if(supervector[i].first == "deleteall"){
            for(int j = 0; j < (int)pos1[a].size(); j++){
                tmp[a][pos1[a][j]] = -1;
                have[a][pos1[a][j]] = 0;
            }
            while(!pos1[a].empty()){
                pos1[a].pop_back();
            }
            sz[a] = 0;
        }
         else if(supervector[i].first == "get"){
            cout << sz[a] << ' ';
            for(int j = 0; j <(int)pos1[a].size(); j++){
                if(tmp[a][pos1[a][j]] != -1){
                    cout << acc1[a][pos1[a][j]] << ' ';

                }
            }
            cout << '\n';
        }
        ///cout << i << "!\n";
    }

}
