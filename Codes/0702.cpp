#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char c[20][20];
bool vis[20];
int cnt, n,k;

int DFS(int row,int step){
    if(step >= k){
        cnt ++;
        return 0;
    }
    for (int i = row; i <n;++i){
        for(int j = 0 ; j < n ;++j){
            if(!vis[j] && c[i][j] == '#'){
                vis[j] = true;
                DFS(i+1,step+1);
                vis[j] = false;
            }
        }
    }
    return 0;
}
int main(){

    while(scanf("%d %d",&n,&k)){
        if(n==-1 && k==-1)
            break;

        memset(vis,0,sizeof(vis));
        memset(c,0,sizeof(c));
        cnt = 0;

        for(int i = 0 ; i < n ; ++i){
            scanf("%s",c[i]);
        }

        DFS(0,0);
        printf("%d\n",cnt);
    }
    return 0;
}
