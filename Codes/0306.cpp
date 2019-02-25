#include<iostream>
#include<stack>
#include<cstdio>
using namespace std;

int main(){
    int n,maxnum = 0;
    scanf("%d",&n);
    stack<int> st;
    for(int i = 0 ;i  < n;++i){
        int tmp ;
        scanf("%d",&tmp);
        if(tmp <1 || tmp >n){
            printf("NO\n");
            break;
        }
        while(st.empty()|| st.top()<tmp){
            int top = ++maxnum;
            printf("PUSH %d\n",top);
            st.push(top);
        }
        printf("POP %d\n",st.top());
        st.pop();
    }
}