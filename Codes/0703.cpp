#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n;
int m[120];
bool foundans= false;
int digits;

int  DFS(int num,int res,int step)
{

    if(res == 0){
        foundans = true;
        digits = step;
    }else if(step<100){
        if(foundans == false){
            m[step] = 0;
            DFS(num,(res *10)% num,step+1);
        }
        if(foundans == false){
            m[step] = 1;
            DFS(num,(res*10+1)% num,step+1);
        }
    }
}

int main(){
    while(scanf("%d",&n) && n){
        foundans = false;
        digits = 0;
        m[0] = 1;

        DFS(n,1%n,1);
        for(int i = 0; i < digits; ++i){
            printf("%d",m[i]);
        }
        printf("\n");
    }
}
