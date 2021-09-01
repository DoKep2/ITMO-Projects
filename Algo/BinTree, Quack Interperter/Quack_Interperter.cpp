#include <bits/stdc++.h>

using namespace std;

int  main()
{
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);
    string s;
    vector<string> order;
    while(cin >> s){
        order.push_back(s);
    }
    int n = order.size();
    queue<unsigned short> q;
    vector<unsigned short> reg(26, 0);
    map<string, int> label;
    for(int i = 0; i < n; i++){
        if(order[i][0] == ':'){
            string t;
            for(int j = 1; j < order[i].size(); j++){
                t.push_back(order[i][j]);
            }
            label[t] = i;
        }
    }
    for(int i = 0; i < n; i++){
            //cout << reg[1] << ' ';
        if(order[i] == "+"){
            unsigned short a = q.front();
            q.pop();
            unsigned short b = q.front();
            q.pop();
            q.push(a + b);
        }
        else if(order[i] == "-"){
            unsigned short a = q.front();
            q.pop();
            unsigned short b = q.front();
            q.pop();
            q.push(a - b);
        }
        else if(order[i] == "*"){
            unsigned short a = q.front();
            q.pop();
            unsigned short b = q.front();
            q.pop();
            q.push(a * b);
        }
        else if(order[i] == "/"){
            unsigned short a = q.front();
            q.pop();
            unsigned short b = q.front();
            q.pop();
            if(b == 0){
                q.push((unsigned short)0);
            }
            else
            q.push(a / b);
        }
        else if(order[i] == "%"){
            unsigned short a = q.front();
            q.pop();
            unsigned short b = q.front();
            q.pop();
            if(b == 0){
                q.push((unsigned short)0);
            }
            else
            q.push(a % b);
        }
        else if(order[i][0] == '>'){
            unsigned short a = q.front();
            q.pop();
            reg[order[i][1] - 'a'] = a;
        }
        else if(order[i][0] == '<'){
            unsigned short a = reg[order[i][1] - 'a'];
            q.push(a);
        }
        else if(order[i] == "P"){
            unsigned short a = q.front();
            q.pop();
            cout << a << '\n';
        }
        else if(order[i][0] == 'P'){
            cout << reg[order[i][1] - 'a'] << '\n';
        }
        else if(order[i] == "C"){
            unsigned short a = q.front();
            a %= 256;
            q.pop();
            cout << char(a);
        }
        else if(order[i][0] == 'C'){
            unsigned short a = reg[order[i][1] - 'a'];
            a %= 256;
            cout << char(a);
        }

        else if(order[i][0] == 'J'){
            string t;
            for(int j = 1; j < order[i].size(); j++){
                t.push_back(order[i][j]);
            }
            i = label[t];
            i--;
            continue;
        }
        else if(order[i][0] == 'Z'){
            unsigned short a = reg[order[i][1] - 'a'];
            if(a == 0){
                string t;
                for(int j = 2; j < order[i].size(); j++){
                    t.push_back(order[i][j]);
                }
                i = label[t];
                i--;
                continue;
            }
        }
        else if(order[i][0] == 'E'){
            unsigned short a = reg[order[i][1] - 'a'];
            unsigned short b = reg[order[i][2] - 'a'];
            if(a == b){
                string t;
                for(int j = 3; j < order[i].size(); j++){
                    t.push_back(order[i][j]);
                }
                i = label[t];
                i--;
                continue;
            }
        }
        else if(order[i][0] == 'G'){
            unsigned short a = reg[order[i][1] - 'a'];
            unsigned short b = reg[order[i][2] - 'a'];
            if(a > b){
                string t;
                for(int j = 3; j < order[i].size(); j++){
                    t.push_back(order[i][j]);
                }
                i = label[t];
                i--;
                continue;
        }
    }
    else if(order[i] == "Q"){
        exit(0);
    }
    else if(order[i][0] != ':'){
        unsigned short num = 0;
        for(int j = 0; j < order[i].size(); j++){
            num *= 10;
            num += (order[i][j] - '0');
        }
        q.push(num);
    }
    }
}
