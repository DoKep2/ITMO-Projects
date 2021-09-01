#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    long long val;
    Node* next;
}Node;

Node* head;

void push_f(long long v, Node** head){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->val = v;
    tmp->next = (*head);
    (*head) = tmp;
}

void pop_f(Node** head){
    *head = (*head)->next;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
    int q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c == '+'){
        int a;
        cin >> a;

            push_f(a, &head);
        }
        else{
            cout << head->val << '\n';
            pop_f(&head);
        }
    }
}
