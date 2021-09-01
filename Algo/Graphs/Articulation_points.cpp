#include <bits/stdc++.h>

using namespace std;

vector<int> d;

vector<int> dp;

vector<int> color;

set<int> s;

vector<vector<pair<int, int> > > graph;

void dfs(int v, int pr = -1, int edge = -1){
    color[v] = 1;
    int children = 0;
    if(pr == -1){
        d[v] = 0;
    }
    else{
        d[v] = d[pr] + 1;
    }
    dp[v] = d[v];
    for(int i = 0; i < graph[v].size(); i++){
        int to = graph[v][i].first;
        if(!color[to]){
            dfs(to, v, graph[v][i].second);
            children++;
            dp[v] = min(dp[v], dp[to]);
        if(dp[to] >= d[v] && pr != -1){
            s.insert(v);
            }
        }
        else if(to != pr){
            dp[v] = min(dp[v], d[to]);
        }
    }
    if(pr == -1 && children >= 2){
        s.insert(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    color.resize(n, 0);
    d.resize(n, 0);
    dp.resize(n);
    graph.resize(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    cout << s.size() << '\n';
    for(auto& i : s){
        cout << i + 1 << ' ';
    }
}
