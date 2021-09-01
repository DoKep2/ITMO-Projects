#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    int v;
    Node* l;
    Node* r;
    Node* p;
}Node;

Node* root;

Node* new_Node(int val, Node* par){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->l = NULL;
    tmp->r = NULL;
    tmp->v = val;
    tmp->p = par;
    return tmp;
}

void push(Node** root, int val){
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

Node* find_val(Node* root, int val){
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


vector<pair<int, pair<int, int> > > tree;

int ans = 0;

void dfs(int v, int h){
    int l = tree[v].second.first;
    int r = tree[v].second.second;
    if(l != -1){
        dfs(l, h + 1);
    }
    if(r != -1){
        dfs(r, h + 1);
    }
    ans = max(ans, h);
}


int  main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
    int n;
    cin >> n;
    tree.resize(n);
    for(int i = 0; i < n; i++){
        cin >> tree[i].first >> tree[i].second.first >> tree[i].second.second;
        tree[i].second.first--;
        tree[i].second.second--;
    }
    if(n == 0){
        cout << 0;
        return 0;
    }
    dfs(0, 1);
    cout << ans;

}
