#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    long long val;
    Node* next;
    Node* prev;
}Node;

Node* head;

Node* tail;

void push_f(Node** head, Node** tail, int v){
    Node* tmp = (Node*)malloc(sizeof(Node));

    tmp->val = v;
    tmp->next = (*head);
    tmp->prev = NULL;
    if(tmp->next != NULL){
        tmp->next->prev = tmp;
    }
    (*head) = tmp;
    if(*tail == NULL){
        (*tail) = tmp;
    }
}

void pop_b(Node** head, Node** tail){

    (*tail) = (*tail)->prev;
    if(*tail == NULL){
        *head = NULL;
    }
    else{
        (*tail)->next = NULL;
    }
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> vec(n);
    for(auto& i : vec){
        cin >> i;
    }
    int q;
    cin >> q;
    while(q--){
        int a;
        cin >> a;
        int l = -1;
        int r = n;
        while(r - l > 1){
            int m = (l + r)/2;
            if(vec[m] >= a){
                r = m;
            }
            else{
                l = m;
            }
        }
        bool check = 0;
        if(r == n || vec[r] != a){
            cout << -1 << ' ';
            check = 1;
        }
        else{
        cout << r + 1 << ' ';
        }
        l = 0;
        r = n;
        while(r - l > 1){
            int m = (l + r)/2;
            if(vec[m] <= a){
                l = m;
            }
            else{
                r = m;
            }
        }
        if(check){
            cout << -1 << '\n';
        }
        else
        cout << l + 1 << '\n';
    }
}
