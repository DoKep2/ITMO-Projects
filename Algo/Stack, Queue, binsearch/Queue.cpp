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
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    int q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c == '+'){
        int a;
        cin >> a;
            push_f(&head, &tail, a);
        }
        else{
            cout << tail->val << '\n';
            pop_b(&head, &tail);
        }
    }
}
