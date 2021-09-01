#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    long long v;
    Node* l;
    Node* r;
    Node* p;
}Node;

Node* root;

Node* new_Node(long long val, Node* par){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->l = NULL;
    tmp->r = NULL;
    tmp->v = val;
    tmp->p = par;
    return tmp;
}

void push(Node** root, long long val){
    Node* tmp = NULL;
    Node* ins = NULL;
    if(*root == NULL){
        *root = new_Node(val, NULL);
        return;
    }
    tmp = *root;
    while(tmp != NULL){
        if(val > tmp->v){
            if(tmp->r != NULL){
                tmp = tmp->r;
                continue;
            }
            else{
                tmp->r = new_Node(val, tmp);
                return;
            }
        }
        else{
            if(tmp->l != NULL){
                tmp = tmp->l;
                continue;
            }
            else{
                tmp->l = new_Node(val, tmp);
                return;
            }
        }
    }
}

Node* get_min(Node* root){
    while(root->l != NULL){
        root = root->l;
    }
    return root;
}

Node* get_max(Node* root){
    while(root->r != NULL){
        root = root->r;
    }
    return root;
}

Node* find_val(Node* root, long long val){
    while(root != NULL){
        if(root->v > val){
            root = root->l;
            continue;
        }
        else if(root->v < val){
            root = root->r;
            continue;
        }
        else{
            return root;
        }
    }
    return NULL;
}


vector<pair<long long, pair<long long, long long> > > tree;

void dfs(long long v, int type){
    long long l = tree[v].second.first;
    long long r = tree[v].second.second;
    if(tree[v].first >= tree[0].first && type == 0){
        cout << "NO";
        exit(0);
    }
    if(tree[v].first <= tree[0].first && type == 1){
        cout << "NO";
        exit(0);
    }
    if(l != -1 && tree[v].first > tree[l].first){
        dfs(l, type);
    }
    else if(l != - 1 && tree[v].first <= tree[l].first){
        cout << "NO";
        exit(0);
    }
    if(r != -1 && tree[v].first < tree[r].first){
        dfs(r, type);
    }
    else if(r != -1 && tree[v].first >= tree[r].first){
        cout << "NO";
        exit(0);
    }
}


int  main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    long long n;
    cin >> n;
    tree.resize(n);
    for(long long i = 0; i < n; i++){
        cin >> tree[i].first >> tree[i].second.first >> tree[i].second.second;
        tree[i].second.first--;
        tree[i].second.second--;
    }
    if(n == 0){
        cout << "YES";
        return 0;
    }
    if(tree[0].second.first != -1){
        if(tree[tree[0].second.first].first >= tree[0].first){
            cout << "NO";
            return 0;
        }
    dfs(tree[0].second.first, 0);
    }
    if(tree[0].second.second != -1){
        if(tree[tree[0].second.second].first <= tree[0].first){
            cout << "NO";
            return 0;
        }
    dfs(tree[0].second.second, 1);
    }
    cout << "YES";

}
