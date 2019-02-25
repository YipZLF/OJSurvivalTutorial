/*

这里有一个重复的子结构：一个表达式对括号里面的部分处理的方式应该和对整个表达式处理的方式是类似的。只是对于整个表达式，判断的是栈是否为空；对括号表达式，判断的是栈顶是否为'('
*/
#include<iostream>
#include<cstdio>
#include<stack>
#include<cmath>
using namespace std;
stack<char> op;
stack<double> num;


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

int str2num(string& str){
    int num = 0,pow = 1;
    for(int i = str.length()-1;i>=0 ;i--){
        num += ((int)str[i]-48) * pow;
        pow *=10;
    }
    return num;
}

double calc(int a,int b,char op){
    double c;
    switch(op){
                        case '+': c = a + b;break;
                        case '-': c = a - b;break;
                        case '*': c = a * b;break;
                        case '/': c = a / b;break;
                        case '^': c = pow(a,b);break;
                }
    return c;
}

int main(){
    freopen("append.in","r",stdin);
    string item;
    while(cin>>item){
            if('0'<=item[0] && item[0]<='9')
                num.push(str2num(item));
            else if(item[0] =='(')
                op.push(item[0]);
            else if(item[0] ==')'){
                while(op.top()!='('){
                    int b = num.top();num.pop();
                    int a = num.top();num.pop();
                    num.push(calc(a,b,op.top()));
                    op.pop();
                    }
                op.pop();
            }
            else{
                while(!op.empty() && op.top()!='(' && !(isPrior(item[0],op.top()))){
                    int b = num.top();num.pop();
                    int a = num.top();num.pop();
                    num.push(calc(a,b,op.top()));
                    op.pop();
                    }
                    op.push(item[0]);
                }

        }
    while(!op.empty() && op.top()!='(' && !(isPrior(item[0],op.top()))){
                    int b = num.top();num.pop();
                    int a = num.top();num.pop();
                    num.push(calc(a,b,op.top()));
                    op.pop();
            }
    cout<<num.top()<<endl;
}

