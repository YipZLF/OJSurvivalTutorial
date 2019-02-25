#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int C[21][21];
char pre[27],post[27];

void calComb(){
    C[0][0] = 1;
    for(int i = 1 ; i <= 21; ++i ){
        C[i][0] = 1;
        C[i][i] = 1;
        for(int j = 1;j<i;++j){
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

int solve(int m,char* preStr,char * postStr,int len){
    int ret = 1;
    int son = 0;
    int i = 1,j = 0;
    while(i<len){
        while(postStr[j]!=preStr[i]){
            j++;
        }
        ++son;
        ret *= solve(m,preStr+i,postStr+i-1,j+2-i);
        i = j+2;
    }
    ret *= C[m][son];
    return ret;
}

int main(){
    calComb();
    int m;
    while(scanf("%d",&m) && m!=0){
        scanf("%s%s",pre,post);
        printf("%d\n",solve(m,pre,post,strlen(pre)));
    }
    return 0;
}