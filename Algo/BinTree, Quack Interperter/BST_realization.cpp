#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    long long v;
    Node* l;
    Node* r;
    Node* p;
}Node;

Node* root = NULL;

void push(Node** root, long long val){
    if(*root == NULL){
        Node* tmp = new Node;
        tmp->v = val;
        tmp->l = NULL;
        tmp->r = NULL;
        tmp->p = NULL;
        *root = tmp;
    }
    else{
        Node* now = *root;
        while(now != NULL){
            if(now->v < val){
                if(now->r != NULL){
                now = now->r;
                }
                else{
                    Node* tmp = new Node;
                    tmp->v = val;
                    tmp->l = NULL;
                    tmp->r = NULL;
                    tmp->p = now;
                    now->r = tmp;
                    return;
                }
            }
            else if(now->v > val){
                if(now->l != NULL){
                    now = now->l;
                }
                else{
                    Node* tmp = new Node;
                    tmp->v = val;
                    tmp->l = NULL;
                    tmp->r = NULL;
                    tmp->p = now;
                    now->l = tmp;
                    return;
                }
            }
            else{
                return;
            }
        }
    }
}

Node** find_(Node** root, long long val){
    while(*root != NULL){
        if((*root)->v > val){
            return find_((&(*root)->l), val);
        }
        else if((*root)->v < val){
            return find_((&(*root)->r), val);
        }
        else{
            return root;
        }
    }
    return NULL;
}

void del1(Node** tmp, Node** p){
    if((*p)->r == NULL){
        (*tmp)->v = (*p)->v;
        *p = (*p)->l;
    }
    else{
        del1(tmp, (&(*p)->r));
    }
}

bool del(Node** head, long long val){
    if(*head == NULL){
        return 0;
    }
    Node* q;
    if(val < (*head)->v){
         return del(&((*head)->l), val);
    }
    else if(val > (*head)->v){
        return del(&((*head)->r), val);
    }
    else{
        q = *head;
        if(q->r == NULL){
            *head = q->l;
        }
        else if(q->l == NULL){
            *head = q->r;
        }
        else{
            del1(&q, &(q->l));
            return 1;
        }
    }
    return 1;
}

long long ans1 = 1e18;

void find_min(Node* root, long long val){
    while(root != NULL){
        if(root->v > val){
            ans1 = min(ans1, root->v);
            root = root->l;
            continue;
        }
        else if(root->v <= val){
            root = root->r;
            continue;
        }
    }
    return;
}

long long ans2 = -1e18;

void find_max(Node* root, long long val){
    while(root != NULL){
        if(root->v >= val){
            root = root->l;
            continue;
        }
        else if(root->v < val){
            ans2 = max(ans2, root->v);
            root = root->r;
            continue;
        }
        else{
            return;
        }
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);
    string s;
    while(cin >> s){
        long long x;
        cin >> x;
        if(s == "insert"){
            push(&root, x);
        }
        else if(s == "delete"){
            del(&root, x);
        }
        else if(s == "exists"){
            if(find_(&root, x)){
                cout << "true\n";
            }
            else{
                cout << "false\n";
            }
        }
        else if(s == "next"){
            find_min(root, x);
            if(ans1 == 1e18){
                cout << "none\n";
            }
            else{
                cout << ans1 << '\n';
            }
            ans1 = 1e18;
        }
        else if(s == "prev"){
            find_max(root, x);
            if(ans2 == -1e18){
                cout << "none\n";
            }
            else{
                cout << ans2 << '\n';
            }
            ans2 = -1e18;
        }
    }
}
