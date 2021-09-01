#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int> > > edges;

vector<int> dp;

vector<int> d;

vector<int> bridges;

vector<int> color;

void dfs(int v, int pr = -1, int edge = -1){
    color[v] = 1;
    if(pr == -1){
        d[v] = 0;
    }
    else{
        d[v] = d[pr] + 1;
    }
    dp[v] = d[v];
    for(int i = 0; i < edges[v].size(); i++){
        int to = edges[v][i].first;
        if(!color[to]){
            dfs(to, v, edges[v][i].second);
            dp[v] = min(dp[v], dp[to]);
        }
        else if(to != pr){
            dp[v] = min(dp[v], d[to]);
        }
    }
    if(dp[v] == d[v] && edge != -1){
        bridges.push_back(edge);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    edges.resize(n);
    color.resize(n, 0);
    d.resize(n, 0);
    dp.resize(n);
    for(int i = 0; i < n; i++){
        dp[i] = i;
    }
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].push_back({b, i});
        edges[b].push_back({a, i});
    }
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    cout << bridges.size() << '\n';
    sort(bridges.begin(), bridges.end());
    for(auto& i : bridges){
        cout << i + 1 << ' ';
    }
}
