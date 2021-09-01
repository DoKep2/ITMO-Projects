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
 ///   freopen("garland.in", "r", stdin);
    ///freopen("garland.out", "w", stdout);
    int n;
    cin >> n;
    long double a;
    cin >> a;
    long double l = 0;
    long double r = 1e9;
    while(r - l > 1e-5){
            int c = 0;
        long double m = (l + r)/2;
        long double ll = 0;
        long double rr = a;
        while(rr - ll > 1e-5){
        int check = 0;
            long double mm = (rr + ll)/2;
            if(2 * mm - a + 2 >= mm || 2 * mm - a + 2 >= a){
                rr = mm;
                continue;
            }
            vector<long double> h(n);
            h[0] = a;
            h[1] = mm;
            int cnt = 0;
            for(int i = 2; i < n; i++){
                h[i] = 2 * h[i - 1] - h[i - 2] + 2;
                if(h[i] < 0){
                    check = 1;
                    break;
                }
                if(h[i] == 0){
                    if(cnt >= 1){
                        check = 1;
                        break;
                    }
                    else cnt++;
                }
            }
            if(h[n - 1] > m){
                check = 2;
            }
            if(check == 1){
                ll = mm;
            }
            else if(check == 2){
                rr = mm;
            }
            else{
                r = m;
                c = 1;
                break;
            }
        }
        if(c != 1){
            l = m;
        }
    }
    cout << fixed << setprecision(10) << r;
}
