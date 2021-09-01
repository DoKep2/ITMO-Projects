#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int> > > graph;

vector<int> color;

vector<int> topsort;

void dfs(int v){
    color[v] = 1;
    for(int i = 0; i < graph[v].size(); i++){
        int to = graph[v][i].first;
        if(!color[to]){
            dfs(to);
        }
    }
    topsort.push_back(v);
}

int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    int n;
    cin >> n;
    graph.resize(n);
    for(int i = 0; i < n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        b--; c--;
        if(b != -1){
        graph[i].push_back({b, 0});
        }
        if(c != -1){
            graph[i].push_back({c, 1});
        }
    }
    color.resize(n);
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    vector<pair<int, int> > kek(n, {0, 0});
    for(int i = 0; i < n; i++){
        if(graph[topsort[i]].size() == 1){
            int to = graph[topsort[i]][0].first;
            if(graph[topsort[i]][0].second == 0){
            kek[topsort[i]] = {max(kek[to].first, kek[to].second) + 1, 0};
            }
            else{
                kek[topsort[i]] = {0, max(kek[to].first, kek[to].second) + 1};
            }
        }
        else if(graph[topsort[i]].size() == 2){
            int to1 = graph[topsort[i]][0].first;
            int to2 = graph[topsort[i]][1].first;
            if(graph[topsort[i]][0].second == 1){
                swap(to1, to2);
            }
            kek[topsort[i]] = {max(kek[to1].first, kek[to1].second) + 1,max(kek[to2].first, kek[to2].second) + 1};
        }
    }
    for(auto& i : kek){
        cout << i.second - i.first << '\n';
    }

}
