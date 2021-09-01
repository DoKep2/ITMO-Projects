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
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    vector<vector<int> > revgraph(n);
    vector<int> in(n);
    color.resize(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        revgraph[b].push_back(a);
        ///in[b]++;
    }
    for(int i = 0; i < n; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    for(int i = 0; i < n; i++){
        if(!color[i]){
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for(int i = 0; i < n - 1; i++){
        int now = topsort[i];
        int to = topsort[i + 1];
        int l = 0;
        int r = graph[now].size();
        if(r == 0){
            cout << "NO";
            return 0;
        }
        while(r - l > 1){
            int m = (l + r)/2;
            if(graph[now][m] > to){
                r = m;
            }
            else{
                l = m;
            }
        }
        if(graph[now][l] != to){
            cout << "NO";
            return 0;
        }

    }
    cout << "YES";


}
