#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > graph;

vector<int> color;

vector<int> way;

vector<int> previ;

void dfs(int v){
    color[v] = 1;
    for(int i = 0; i < graph[v].size(); i++){
        int to = graph[v][i];
        if(!color[to]){
            previ[to] = v;
            dfs(to);
        }
        else if(color[to] == 1){
            cout << "YES\n";
        way.push_back(to);
        int vv = v;
        while(vv != to && previ[vv] != -1){
            way.push_back(vv);
            vv = previ[vv];
        }
        reverse(way.begin(), way.end());
        for(auto& i : way){
            cout << i + 1 << ' ';
        }
        exit(0);
        }
    }
    color[v] = 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    color.resize(n);
    previ.resize(n, -1);
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
    cout << "NO";

}
