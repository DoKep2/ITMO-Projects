#include <bits/stdc++.h>

using namespace std;

long long cnt = 2;

vector<vector<long long> > graph;

vector<pair<long long, long long> > kek;

vector<long long> num;

vector<long long> val;

long long n;

long long root = -1;

void leftrot(long long v, long long pr, long long type, long long check)
{
    if(kek[v].second - kek[v].first <= 1 && check)
    {
        return;
    }
    long long to1 = graph[v][1];
    ///cout << v << ' ' << pr << ' ' << type << '\n';
    if(to1 == -1)
    {
        return;
    }
    graph[v][1] = graph[to1][0];
    graph[to1][0] = v;
    kek[v].second = kek[to1].first;
    kek[to1].first = max(kek[v].first, kek[v].second) + 1;
    if(pr != -1)
    {
        graph[pr][type] = to1;
        if(type == 0)
        {
            kek[pr].first = max(kek[to1].first, kek[to1].second) + 1;
        }
        else
        {
            kek[pr].second = max(kek[to1].first, kek[to1].second) + 1;
        }
    }
    if(v == root)
    {
        root = to1;
    }
}

void rightrot(long long v, long long pr, long long type, long long check)
{
    if(kek[v].second - kek[v].first >= -1 && check)
    {
        return;
    }
    long long to1 = graph[v][0];
    if(to1 == -1)
    {
        return;
    }
    graph[v][0] = graph[to1][1];
    graph[to1][1] = v;
    kek[v].first = kek[to1].second;
    kek[to1].second = max(kek[v].first, kek[v].second) + 1;
    if(pr != -1)
    {
        graph[pr][type] = to1;
        if(type == 0)
        {
            kek[pr].first = max(kek[to1].first, kek[to1].second) + 1;
        }
        else
        {
            kek[pr].second = max(kek[to1].first, kek[to1].second) + 1;
        }
    }
    if(v == root)
    {
        root = to1;
    }
}

void bigleft(long long v, long long pr, long long type)
{
    if(kek[v].second - kek[v].first > 1 && graph[v][1] != -1 && kek[graph[v][1]].second - kek[graph[v][1]].first == -1)
    {
        rightrot(graph[v][1], v, 1, 0);
        leftrot(v, pr, type, 0);
    }
}

void bigright(long long v, long long pr, long long type)
{
    if(kek[v].second - kek[v].first < -1 && graph[v][0] != -1 && kek[graph[v][0]].second - kek[graph[v][0]].first == 1)
    {
        leftrot(graph[v][0], v, 0, 0);
        rightrot(v, pr, type, 0);
    }
}


/*
4
10 2 3
4 0 0
7 0 4
8 0 0
4*/
pair<long long, pair<long long, long long> > find_(long long v, long long pr, long long type)
{
    if(graph[v][1] != -1)
    {
        return find_(graph[v][1], v, 1);
    }
    else
    {
        return {v, {pr, type}};
    }
}

bool exists(int v, int key)
{
    if(val[v] > key)
    {
        if(graph[v][0] == -1)
        {
            return 0;
        }
        else
            return exists(graph[v][0], key);
    }
    else if(val[v] < key)
    {
        if(graph[v][1] == -1)
        {
            return 0;
        }
        else
            return exists(graph[v][1], key);
    }
    else
    {
        return 1;
    }
}

void delete_(long long x, long long v, long long pr, long long type)
{
    if(val[v] > x)
    {
        if(graph[v][0] != -1)
        {
            delete_(x, graph[v][0], v, 0);
            if(graph[v][0] != -1)
            {
                kek[v].first = max(kek[graph[v][0]].first, kek[graph[v][0]].second) + 1;
            }
            else
            {
                kek[v].first = 0;
            }
            bigleft(v, pr, type);
            bigright(v, pr, type);
            leftrot(v, pr, type, 1);
            rightrot(v, pr, type, 1);

            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else
        {
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
    else if(val[v] < x)
    {
        if(graph[v][1] != -1)
        {
            delete_(x, graph[v][1], v, 1);
            if(graph[v][1] != -1)
            {
                kek[v].second = max(kek[graph[v][1]].second, kek[graph[v][1]].first) + 1;
            }
            else
            {
                kek[v].second = 0;
            }
            bigleft(v, pr, type);
            bigright(v, pr, type);
            leftrot(v, pr, type, 1);
            rightrot(v, pr, type, 1);


            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else
        {
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
    else
    {
        if(graph[v][0] == -1 && graph[v][1] == -1)
        {
            graph[pr][type] = -1;
            ///  cout << pr << ' ' << type << '\n';
            if(type == 0)
            {
                kek[pr].first = 0;
            }
            else
            {
                kek[pr].second = 0;
            }
        }
        else if(graph[v][0] == -1)
        {
            if(pr != -1)
            {
                graph[pr][type] = graph[v][1];
                if(type == 0)
                {
                    kek[pr].first = 1;
                }
                else
                {
                    kek[pr].second = 1;
                }
            }
            else
            {
                root = graph[v][1];
            }
        }
        else
        {
            pair<long long, pair<long long, long long> > r = find_(graph[v][0], v, 0);
            val[v] = val[r.first];
            delete_(val[r.first], graph[v][0], v, 0);
            if(graph[v][0] != -1)
            {
                kek[v].first = max(kek[graph[v][0]].second, kek[graph[v][0]].first) + 1;
            }

            else
            {
                kek[v].first = 0;
            }
            bigleft(v, pr, type);
            bigright(v, pr, type);
            leftrot(v, pr, type, 1);
            rightrot(v, pr, type, 1);
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
}

void push(int x, int v, int k)
{
    if(val[v] > x)
    {
        if(graph[v][0] != -1)
        {
            push(x, graph[v][0], k);
            kek[v].first = max(kek[graph[v][0]].first, kek[graph[v][0]].second) + 1;
            bigleft(graph[v][0], v, 0);
            bigright(graph[v][0], v, 0);
            leftrot(graph[v][0], v, 0, 1);
            rightrot(graph[v][0], v, 0, 1);
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else
        {
            kek[v].first = 1;
            graph[v][0] = k;
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
    else if(val[v] < x)
    {
        if(graph[v][1] != -1)
        {
            push(x, graph[v][1], k);
            kek[v].second = max(kek[graph[v][1]].second, kek[graph[v][1]].first) + 1;
            bigleft(graph[v][1], v, 1);
            bigright(graph[v][1], v, 1);
            leftrot(graph[v][1], v, 1, 1);
            rightrot(graph[v][1], v, 1, 1);
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
        else
        {
            kek[v].second = 1;
            graph[v][1] = k;
            if(v == root)
            {
                bigleft(v, -1, -1);
                bigright(v, -1, -1);
                leftrot(v, -1, -1, 1);
                rightrot(v, -1, -1, 1);
            }
        }
    }
    else
    {
        return;
    }
}

int main()

{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k = 0;
     freopen("avlset.in", "r", stdin);
     freopen("avlset.out", "w", stdout);
    cin >> n;
    graph.resize(n, vector<long long>(2, -1));
    val.resize(n);
    kek.resize(n, {0, 0});
    for(int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        int a;
        cin >> a;
        if(c == 'A')
        {
            if(root == -1)
            {
                root = k;
                cout << 0 << '\n';
                val[k] = a;
                k++;
                continue;
            }

            if(exists(root, a))
            {
                cout << kek[root].second - kek[root].first << '\n';
                continue;
            }

            val[k] = a;
            push(a, root, k);
            cout << kek[root].second - kek[root].first << '\n';
            k++;
        }
        else if(c == 'D')
        {
            if(root == -1)
            {
                cout << 0 << '\n';
                continue;
            }
            if(!exists(root, a))
            {
                cout << kek[root].second - kek[root].first << '\n';
                continue;
            }
            if(graph[root][0] == -1 && graph[root][1] == -1)
            {
                cout << 0 << '\n';
                root = -1;
                continue;
            }
            delete_(a, root, -1, -1);
            cout << kek[root].second - kek[root].first << '\n';
        }
        else
        {
            if(root == -1)
            {
                cout << "N\n";
                continue;
            }
            if(exists(root, a))
            {
                cout << "Y\n";
            }
            else
            {
                cout << "N\n";
            }
        }
    }
}
