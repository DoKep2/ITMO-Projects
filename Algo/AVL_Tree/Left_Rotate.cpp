#include <bits/stdc++.h>

using namespace std;

long long cnt = 2;

vector<vector<long long> > graph;

vector<long long> color;

vector<long long> topsort;

vector<pair<long long, long long> > kek;

vector<long long> num;

vector<long long> val;

long long n;

void dfs(long long v)
{
    color[v] = 1;
    for(long long i = 0; i < graph[v].size(); i++)
    {
        long long to = graph[v][i];
        if(!color[to])
        {
            dfs(to);
        }
    }
    topsort.push_back(v);
}

void print (long long v)
{
    queue<long long> q;
    q.push(v);
    while(!q.empty())
    {
        long long vv = q.front();
        q.pop();
        cout << val[vv] << ' ';
        if(cnt > n || (graph[vv][0] == -1 && graph[vv][1] == -1))
        {
            cout << 0 << ' ' << 0 << '\n';
            if(graph[vv][0] != -1)
            {
                q.push(graph[vv][0]);
            }
            if(graph[vv][1] != -1)
            {
                q.push(graph[vv][1]);
            }
            continue;
        }
        else if(graph[vv][0] == -1)
        {
            cout << 0 << ' ' <<  cnt++ << '\n';
            if(graph[vv][0] != -1)
            {
                q.push(graph[vv][0]);
            }
            if(graph[vv][1] != -1)
            {
                q.push(graph[vv][1]);
            }
            continue;
        }
        else
        {
            cout << cnt++ << ' ';
        }
        if(cnt > n || graph[vv][1] == -1)
        {
            cout << 0 << '\n';
        }
        else
        {
            cout << cnt++ << '\n';
        }
        if(graph[vv][0] != -1)
        {
            q.push(graph[vv][0]);
        }
        if(graph[vv][1] != -1)
        {
            q.push(graph[vv][1]);
        }
    }
}

void rotate_(long long v)
{
    if(graph[v][1] != -1 && kek[graph[v][1]].second - kek[graph[v][1]].first == -1)
    {
        long long to1 = graph[v][1];
        if(to1 == -1)
        {
            return;
        }
        long long to2 = graph[to1][0];
        if(to2 == -1)
        {
            return;
        }
        long long to3 = graph[to2][0];
        long long to4 = graph[to2][1];
        long long to5 = graph[to1][1];
        graph[v][1] = to3;
        graph[to1][0] = to4;
        graph[to2][0] = v;
        graph[to2][1] = to1;
        kek[v].second = kek[to2].first;
        kek[to1].first = kek[to2].second;
        kek[to2].first = max(kek[v].first, kek[v].second);
        kek[to2].second = max(kek[to1].first, kek[to1].second);
        print(to2);
        exit(0);
    }
    else
    {
        long long to1 = graph[v][1];
        if(to1 == -1)
        {
            return;
        }
        long long to2 = graph[to1][0];
        long long to3 = graph[to1][1];
        graph[v][1] = to2;
        graph[to1][0] = v;
        kek[v].second = kek[to1].first;
        kek[to1].first = max(kek[v].first, kek[v].second);
        print(to1);
    }


}

int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);

    cin >> n;
    cout << n << '\n';
    graph.resize(n, vector<long long>(2, -1));
    val.resize(n);
    for(long long i = 0; i < n; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        val[i] = a;
        b--;
        c--;
        if(b != -1)
        {
            graph[i][0] = b;
        }
        if(c != -1)
        {
            graph[i][1] = c;
        }
    }
    color.resize(n);
    for(long long i = 0; i < n; i++)
    {
        if(!color[i])
        {
            dfs(i);
        }
    }
    kek.resize(n, {0, 0});
    for(long long i = 0; i < n; i++)
    {
        if(graph[topsort[i]][1] == -1 && graph[topsort[i]][0] == -1)
        {
            continue;
        }
        if(graph[topsort[i]][1] == -1)
        {
            long long to = graph[topsort[i]][0];
            kek[topsort[i]] = {max(kek[to].first, kek[to].second) + 1, 0};
        }
        else if(graph[topsort[i]][0] == -1)
        {
            long long to = graph[topsort[i]][1];
            kek[topsort[i]] = {0, max(kek[to].first, kek[to].second) + 1};
        }
        else
        {
            long long to1 = graph[topsort[i]][0];
            long long to2 = graph[topsort[i]][1];
            kek[topsort[i]] = {max(kek[to1].first, kek[to1].second) + 1,max(kek[to2].first, kek[to2].second) + 1};
        }
    }
    rotate_(0);
}
