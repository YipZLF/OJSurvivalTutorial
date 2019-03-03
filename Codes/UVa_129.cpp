#include<iostream>
#include<cstdio>
const int MAXN = 90;
char A[MAXN];
int n,L;
int idx;

bool isValid(int cur){
    for(int i = 1; 2*i <= cur+1;++i ){
        bool flag = false;
        for(int j = 0 ;j <i;++j){
            if(A[cur-j] != A[cur-j-i])
                {flag = true;break;}
        }
        if(flag == false)
            return false;
    }
    return true;
}

void PrintA(int cur){
    for(int i = 0 ; i <= cur;++i){
        if(i!=0 && i%4==0){
            putchar(' ');
        }
        if(i!=0 && i%(16*4)==0){
            putchar('\n');
        }
        printf("%c",A[i]);
    }
    printf("\n%d\n",cur+1);
}

void dfs(int cur){
    for(int i = 0 ; i< L && idx< n;++i){
        A[cur] = 'A'+i;
        if(isValid(cur)){
            idx++;
            if(idx==n){
                PrintA(cur);
                return;
            }
            dfs(cur+1);
        }else{
            continue;
        }
    }
    return;
}

int main(){
    while(scanf("%d %d",&n,&L) && n!=0){
        idx = 0;
        dfs(0);
    }
}
