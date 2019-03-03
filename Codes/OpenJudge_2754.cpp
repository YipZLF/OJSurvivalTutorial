#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 8;
bool vis[3][2*MAXN];
int C[MAXN];
int n,idx;
void search(int cur,int m){
    if(cur == n){
        idx++;
        if(idx==m){
            for(int i =0 ;i  < n;++i){
                printf("%d",C[i]);
            }
            printf("\n");
        }
        return ;
    }
    else{
        for(int i = 0 ; i < n ;i++){
            if(!vis[0][i] && !vis[1][cur+i] && !vis[2][(cur-i+n)]){
                C[cur] = i+1;
                vis[0][i] = vis[1][cur+i] = vis[2][(cur-i+n)] = true;
                search(cur+1,m);
                vis[0][i] = vis[1][cur+i] = vis[2][(cur-i+n)] = false;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    n = MAXN;
    int m;
    while(T--){
        idx = 0;
        scanf("%d",&m);
        search(0,m);   
    }
    return 0;
}