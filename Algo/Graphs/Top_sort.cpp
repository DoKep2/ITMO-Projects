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
        else if(color[to] == 1){
            cout << -1;
            exit(0);
        }
    }
    topsort.push_back(v);
    color[v] = 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    color.resize(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
    }
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for(auto& i : topsort){
        cout << i + 1 << ' ';
    }

}
