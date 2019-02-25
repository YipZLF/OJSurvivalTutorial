#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
stack<char> st;

bool isPrior(char op1,char op2)
{
    if(op1=='^')
        op1 = 2;
    else if(op1=='*'||op1=='/')
        op1 = 1;
    else
        op1 = 0;
    if(op2=='^')
        op2 = 2;
    else if(op2=='*'||op2=='/')
        op2 = 1;
    else
        op2 = 0;
    return op1>op2;
}

int main()
{
    freopen("append.in","r",stdin);
    char expr[10];
    string append,tmp;
    int result,i =0;

    while(scanf("%s",expr)==1){
        switch(expr[0]){
            case '(':{st.push(expr[0]);break;}
            case ')':{
                while(st.top()!='('){
                    append = append + st.top()+' ';
                    st.pop();}
                st.pop();
                break;}
            case '^':
            case '*':
            case '/':
            case '+':
            case '-':{
                while(true){
                    if(!st.empty() && st.top()!='(' && !(isPrior(expr[0],st.top()))){
                            append = append + st.top()+' ';
                            st.pop();
                        }
                    else{st.push(expr[0]);break;}
                    }
                    break;
                    }
            default:append = append + expr + ' ';
            }
        }
    while(st.size()>0){
        append = append + st.top() + ' ';
        st.pop();
    }


    cout<<append<<endl;


}
