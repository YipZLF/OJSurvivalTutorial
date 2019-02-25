#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int C[1030][1030];

int lowbit(int x){
    return x&(-x);
}

void change(int x, int y, int a,int S)
{
    for(int j = x; j <= S; j = j + lowbit(j)){
        for(int i = y; i <= S; i = i + lowbit(i)){
            C[i][j] += a;
        }
    }
}

int Sum(int x,int y)
{
    int sum = 0;
    for(int j = x; j > 0 ;j = j- lowbit(j)){
        for(int i = y; i > 0; i = i - lowbit(i)){
            sum +=  C[i][j];
        }
    }
    return sum;
}

int main()
{
    int op,S,X,Y,A,L,B,R,T;
    while(scanf("%d ",&op)==1){
        if(op == 3) break;
        else if(op == 0){
            scanf("%d",&S);
        }else if(op == 1){
            scanf("%d %d %d",&X,&Y,&A);
            change(X+1,Y+1,A,S);
        }else if(op == 2){
            scanf("%d %d %d %d",&L,&B,&R,&T);
            printf("%d\n",
                   Sum(R+1,T+1)-Sum(L,T+1)-Sum(R+1,B)+Sum(L,B));
        }
    }
}
