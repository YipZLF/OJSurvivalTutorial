#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 50020
using namespace std;
int type[MAXN],parent[MAXN],fake = 0,N,K;

int main(){
    scanf("%d %d",&N,&K);
    fake = 0;
    for(int i = 0  ;i<N;++i){
        parent[i] = i;
        type[i] = -1;
    }
    for(int j = 0 ;j <K;++j){
        int op,a,b;
        scanf("%d %d %d",&op,&a,&b);
        if(a>N || b>N){
            fake++;
            continue;
        }
        if(op==1){
            int pa = root(a);
            int pb = root(b);
            if(type[pa]!=-1 &&type[pb]!=-1){
               if(type[pa]!=type[pb] )
                    fake++;
               else{//merge
                    parent[pb] = pa;
                }
            }else{
                parent[pb] = pa;
                if(type[pa]==-1 && type[pb]!=-1)
                    type[pa] = type[pb];
            }
        }
    }
}

