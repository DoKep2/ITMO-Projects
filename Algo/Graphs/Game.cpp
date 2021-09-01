#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > graph;

vector<int> color;

vector<int> topsort;

void dfs(int v){
    color[v] = 1;
    for(int i = 0; i < graph[v].size(); i++){
        int to = graph[v][i];
        if(!color[to]){
            dfs(to);
        }
    }
    topsort.push_back(v);
}



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    graph.resize(n);
    vector<int> out(n);
    vector<vector<int> > revgraph(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        revgraph[b].push_back(a);
        out[a]++;
    }
    vector<int> dp(n);
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(!out[i]){
            q.push(i);
        }
    }
    vector<bool> was(n, false);
    while(!q.empty()){
        int v = q.front();
        was[v] = 1;
        q.pop();
        for(int i = 0; i < revgraph[v].size(); i++){
            int to = revgraph[v][i];
            if(!dp[v] && !dp[to]){
                dp[to] = 1;
            }
            if(!was[to])
            q.push(to);
        }
    }
    if(dp[s]){
        cout << "First player wins";
    }
    else{
        cout << "Second player wins";
    }

}
