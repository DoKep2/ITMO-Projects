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

int root;

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
        if(cnt > n + 1 || (graph[vv][0] == -1 && graph[vv][1] == -1))
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
        if(cnt > n + 1 || graph[vv][1] == -1)
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
/*6
3 2 3
2 0 0
10 4 5
7 6 0
12 0 0
4 0 0
8*/

/*
4
5 2 3
3 0 0
7 0 4
10 0 0
15
*/
/*
5
1 0 2
10 0 3
100 0 4
1000 0 5
10000 0 0
-5*/

/*8
10 2 3
7 4 5
20 6 0
4 0 0
9 0 0
15 7 8
12 0 0
16 0 0
22
*/

void leftrot(int v, int pr, int type, int check){
    if(kek[v].second - kek[v].first <= 1 && check){
        return;
    }
    int to1 = graph[v][1];
    ///cout << v << ' ' << pr << ' ' << type << '\n';
    if(to1 == -1){
        return;
    }
    graph[v][1] = graph[to1][0];
    graph[to1][0] = v;
    kek[v].second = kek[to1].first;
    kek[to1].first = max(kek[v].first, kek[v].second) + 1;
    if(pr != -1){
        graph[pr][type] = to1;
        if(type == 0){
            kek[pr].first = max(kek[to1].first, kek[to1].second) + 1;
        }
        else{
            kek[pr].second = max(kek[to1].first, kek[to1].second) + 1;
        }
    }
    if(v == root){
        root = to1;
    }
}

void rightrot(int v, int pr, int type, int check){
    if(kek[v].second - kek[v].first >= -1 && check){
        return;
    }
    int to1 = graph[v][0];
    if(to1 == -1){
        return;
    }
    graph[v][0] = graph[to1][1];
    graph[to1][1] = v;
    kek[v].first = kek[to1].second;
    kek[to1].second = max(kek[v].first, kek[v].second) + 1;
    if(pr != -1){
        graph[pr][type] = to1;
        if(type == 0){
            kek[pr].first = max(kek[to1].first, kek[to1].second) + 1;
        }
        else{
            kek[pr].second = max(kek[to1].first, kek[to1].second) + 1;
        }
    }
    if(v == root){
        root = to1;
    }
}

void bigleft(int v, int pr, int type){
    if(kek[v].second - kek[v].first > 1 && graph[v][1] != -1 && kek[graph[v][1]].second - kek[graph[v][1]].first == -1){
        rightrot(graph[v][1], v, 1, 0);
        leftrot(v, pr, type, 0);
    }
}

void bigright(int v, int pr, int type){
    if(kek[v].second - kek[v].first < -1 && graph[v][0] != -1 && kek[graph[v][0]].second - kek[graph[v][0]].first == 1){
        leftrot(graph[v][0], v, 0, 0);
        rightrot(v, pr, type, 0);
    }
}

void push(int x, int v){
    if(val[v] > x){
        if(graph[v][0] != -1){
            push(x, graph[v][0]);
            kek[v].first = max(kek[graph[v][0]].first, kek[graph[v][0]].second) + 1;
            bigleft(graph[v][0], v, 0);
            bigright(graph[v][0], v, 0);
            leftrot(graph[v][0], v, 0, 1);
            rightrot(graph[v][0], v, 0, 1);
            if(v == root){
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else{
            kek[v].first = 1;
            graph[v][0] = n;
            if(v == root){
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
    else{
        if(graph[v][1] != -1){
            push(x, graph[v][1]);
            kek[v].second = max(kek[graph[v][1]].second, kek[graph[v][1]].first) + 1;
                bigleft(graph[v][1], v, 1);
                bigright(graph[v][1], v, 1);
                leftrot(graph[v][1], v, 1, 1);
                rightrot(graph[v][1], v, 1, 1);
             if(v == root){
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else{
            kek[v].second = 1;
            graph[v][1] = n;
            if(v == root){
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
}

int main()

{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("addition.in", "r", stdin);
    freopen("addition.out", "w", stdout);
    cin >> n;
    graph.resize(n + 1, vector<long long>(2, -1));
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
    kek.resize(n + 1, {0, 0});
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
    int x;
    cin >> x;
    if(n == 0){
        cout << 1 << '\n';
        cout << x << ' ' << 0 << ' ' << 0;
        return 0;
    }
    cout << n + 1 << '\n';
    val.push_back(x);
    graph[n][0] = -1;
    graph[n][1] = -1;
    push(x, 0);
    print(root);
}
