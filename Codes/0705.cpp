#include<iostream>
#include<cstdio>
#include<string>
#define INF 0xfffffff
using namespace std;
int N, Q;
int G[2010][2010];
int lowdis[2010];

struct node{
    char str[7];
}cars[2010];

int main(){
    while(scanf("%d",&N)==1 & N!= 0){
        for(int i = 0 ; i <N ;i++){
            scanf("%s",cars[i].str);
            for(int j = 0 ; j <i;j++){
                int w=0;
                for(int k = 0 ;k <7;k++){
                    if(cars[i].str[k]!=cars[j].str[k])
                        w++;
                }
                G[i][j] = G[j][i] = w;
            }
        }

        Q = 0;
        for(int i = 0 ;i < N; ++i)
            lowdis[i] = G[0][i];
        for(int i = 0 ; i < N-1;++i){
            int minW = INF,k = 0;
            for(int j = 0 ; j <N; ++j){
                if(lowdis[j]!= 0 && lowdis[j]<minW){
                    minW = lowdis[j];
                    k = j;
                }
            }
            Q += minW;
            lowdis[k] = 0;
            for(int l = 0 ; l<N;++l){
                if(G[k][l]<lowdis[l])
                    lowdis[l] = G[k][l];
            }
        }

        printf("The highest possible quality is 1/%d.\n",Q);
    };

}
