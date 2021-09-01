#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > graph;

vector<int> type;

void bfs(int v){
    type[v] = 0;
    queue<int> q;
    q.push(v);
    while(!q.empty()){
        int vv = q.front();
        q.pop();
        for(int i = 0; i < graph[vv].size(); i++){
            int to = graph[vv][i];
            if(type[to] != -1 && type[to] == type[vv]){
                cout << "NO";
                exit(0);
            }
            if(type[to] != -1){
                continue;
            }
            if(type[vv] == 0){
                type[to] = 1;
            }
            else{
                type[to] = 0;
            }
            q.push(to);
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    type.resize(n, -1);
    for(int i = 0; i < n; i++){
        if(type[i] == -1){
            bfs(i);
        }
    }
    cout << "YES";
}
