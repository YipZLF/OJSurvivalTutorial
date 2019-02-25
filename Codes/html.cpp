#include<iostream>
#include<cstdio>
#include<string>
#include<stack>
using namespace std;

int main(){
    freopen("html.in","r",stdin);
    stack<string> st;
    string open,close;
    bool isValid = true;
    char c;
    while(scanf("%c",&c)==1){
        if(c=='<'){
            char next;
            string tmp;
            scanf("%c",&next);
            if(next!='/'){
                getline(cin,open,'>');
                open = next+open;
                st.push(open);
            }else{
                getline(cin,close,'>');
                tmp = st.top();
                st.pop();
                if(tmp!=close){
                    isValid = false;
                    break;
                }
            }
        }
    }
    if(!(st.empty())){
        isValid=false;
    }
    printf((isValid)?"True":"False");
    return 0;
}


