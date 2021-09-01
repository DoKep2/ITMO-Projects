#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > graph;

vector<int> topsort;

vector<int> color;

vector<int> comp;

vector<vector<int> > revgraph;

set<pair<int, int> > edges;

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

void rev_dfs(int v, int cur_comp){
    comp[v] = cur_comp;
    for(int i = 0; i < revgraph[v].size(); i++){
        int to = revgraph[v][i];
        if(comp[to] == -1){
            rev_dfs(to, cur_comp);
        }
        else if(comp[to] != cur_comp){
            edges.insert({comp[v], comp[to]});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    revgraph.resize(n);
    color.resize(n, 0);
    comp.resize(n, -1);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        revgraph[b].push_back(a);
    }
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    int cur_comp = 0;
    for(int i = 0; i < n; i++){
        if(comp[topsort[i]] == -1){
            rev_dfs(topsort[i], cur_comp);
            cur_comp++;
        }
    }
    cout << cur_comp << '\n';
    for(auto& i : comp){
        cout << i + 1 << ' ' ;
    }
}
