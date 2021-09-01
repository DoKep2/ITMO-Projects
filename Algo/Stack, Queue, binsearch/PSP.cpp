#include <bits/stdc++.h>

using namespace std;

typedef struct Node{
    char val;
    Node* next;
}Node;

Node* head = NULL;

void push_f(Node** head, char v){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->val = v;
    tmp->next = (*head);
    (*head) = tmp;
}
void pop_f(Node** head){
    (*head) = (*head)->next;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);

    string s;
    while(cin >> s){
            bool check = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '(' || s[i] == '['){
            push_f(&head, s[i]);
           }
           else{
            if(s[i] == ')'){
                if( head == NULL || head->val != '('){

                    check = 1;
                    break;
                   }
                   else{
                    pop_f(&head);
                   }
            }
            else{
                if(head == NULL || head->val != '['){

                    check = 1;
                    break;
                   }
                   else{
                    pop_f(&head);
                   }
            }
           }
    }

    if(head == NULL && !check){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
    head = NULL;
    }
}
