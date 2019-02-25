#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int Next[1000100];
char str[1000100];

void getNext(char* P){
    int i,k;
    int m = strlen(P);
    Next[0] = -1;
    i = 0 ; k = -1;
    while(i < m-1){//只需要填入到m-1，然而next[m-1]只和next[m-2]以及其以前的有关系
        while(k>=0 && P[i]!=P[k])
            k = Next[k];
        i++;k++;
        Next[i] = k;
    }
    return ;
}

int main(){
    int len = 0,numcase;
    for(numcase=1;scanf("%d",&len)&&len!=0;numcase++){
        memset(str,0,sizeof(str));
        memset(Next,0,sizeof(Next));
        scanf("%s",str);
        getNext(str);
        if(str[len-1]==str[Next[len-1]])
            Next[len]=Next[len-1]+1;
        printf("Test case #%d\n",numcase);
        for(int i = 2;i<=len;++i){
            if(i % (i -Next[i])==0 && Next[i]!=0)
                printf("%d %d\n",i,i/(i - Next[i]));
        }
        printf("\n");
    }
}